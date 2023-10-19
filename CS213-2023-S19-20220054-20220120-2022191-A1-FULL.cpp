// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				PhotoEditor.cpp
// Last Modification Date:	10/10/2013
// Author1 and ID:	Osama Amrawy 20220054
// Author2 and ID:	Abdelrahman Saeed 20220191
// Author3 and ID:	Khaled Mostafa 20220120

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage() {
    char imageFileName[100];

    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}


void saveImage() {
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void black_and_WhiteFilter() {
    //all pixels higher than 127 totally white and any other totally black
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}


void InvertImage() {
    //just inverting color by subtract the pixel from 255
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];
        }
    }
}


void MergeImages() {
    //takes the average of every pixel with the other pixel in the other photo
    char otherimageFileName[100];
    unsigned char result[SIZE][SIZE];
    unsigned char otherimage[SIZE][SIZE];

    cout << "Please enter name of image file to merge with: ";
    cin >> otherimageFileName;

    strcat(otherimageFileName, ".bmp");
    readGSBMP(otherimageFileName, otherimage);
    char resFileName[100];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = (image[i][j] + otherimage[i][j]) / 2;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = result[i][j];
        }
    }
}

void FlipImage() {
    char c;
    cout << "Flip (h)orizontally or (v)ertically ?";
    cin >> c;
    if (c == 'h') {
        //switching vertical pixels to flip horizontally
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                int temp;
                temp = image[i][j];
                image[i][j] = image[i][255 - j];
                image[i][255 - j] = temp;

            }
        }
    } else if (c == 'v') {
        //switching horizontal pixels to flip vertically
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                int temp;
                temp = image[j][i];
                image[j][i] = image[255 - j][i];
                image[255 - j][i] = temp;
            }
        }
    }
}


void DarkenAndLighten() {
    char c;
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> c;
    if (c == 'd') {
        //making all pixels with the half values to be darker
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[i][j] / 2;
            }
        }
    } else if (c == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[i][j] + (255 - image[i][j]) / 2;
            }
        }
    }
}


void Mirror() {
    unsigned char other[SIZE][SIZE];
    char s;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?";
    cin >> s;
    if (s == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                other[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                int temp;
                temp = image[i][j];
                image[i][j] = image[i][255 - j];
                image[i][255 - j] = temp;

            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 127; j < SIZE; ++j) {
                other[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = other[i][j];
            }
        }
    } else if (s == 'r') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 127; j < SIZE; ++j) {
                other[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                int temp;
                temp = image[i][j];
                image[i][j] = image[i][255 - j];
                image[i][255 - j] = temp;

            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                other[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = other[i][j];
            }
        }
    } else if (s == 'u') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                other[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                int temp;
                temp = image[j][i];
                image[j][i] = image[255 - j][i];
                image[255 - j][i] = temp;
            }
        }
        for (int i = 127; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                other[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = other[i][j];
            }
        }
    } else if (s == 'd') {
        for (int i = 127; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                other[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                int temp;
                temp = image[j][i];
                image[j][i] = image[255 - j][i];
                image[255 - j][i] = temp;
            }
        }
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                other[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = other[i][j];
            }
        }
    }
}

void Rotate() {
    unsigned char other[SIZE][SIZE];
    int x;
    cout << "Rotate (90), (180) or (270) degrees?";
    cin >> x;
    if (x == 90) {
        for (int i = SIZE - 1; i >= 0; --i) {
            for (int j = 0; j < SIZE; j++) {
                other[j][i] = image[SIZE - i - 1][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = other[i][j];
            }
        }
    } else if (x == 180) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                int temp = image[i][j];
                image[i][j] = image[i][255 - j];
                image[i][255 - j] = temp;

            }
        }
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int temp = image[i][j];
                image[i][j] = image[255 - i][j];
                image[255 - i][j] = temp;
            }
        }
    } else if (x == 270) {
        for (int i = SIZE - 1; i >= 0; --i) {
            for (int j = 0; j < SIZE; ++j) {
                other[j][i] = image[SIZE - i - 1][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = other[i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                int temp = image[i][j];
                image[i][j] = image[i][255 - j];
                image[i][255 - j] = temp;
            }
        }
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int temp = image[i][j];
                image[i][j] = image[255 - i][j];
                image[255 - i][j] = temp;
            }
        }
    }
}

void crop() {
    unsigned char other[SIZE][SIZE];
    int x, y, w, l;
    cout << "Please enter x y l w: ";
    cin >> x >> y >> l >> w;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            other[i][j] = 255;
        }
    }
    for (int i = x; i < l + x; ++i) {
        for (int j = y; j < w + y; ++j) {
            other[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = other[i][j];
        }
    }
}


void DetectImageEdges() {
    unsigned char other[SIZE][SIZE];
    black_and_WhiteFilter();
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            if (image[i + 1][j] != image[i - 1][j] || image[i][j + 1] != image[i][j - 1]) {
                other[i][j] = 0;
            } else {
                other[i][j] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = other[i][j];
        }
    }
}


void blur() {
    unsigned char other[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            other[i][j] = image[i][j];
        }
    }
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            image[i][j] =
                    (other[i][j + 1] + other[i][j - 1] + other[i - 1][j - 1] + other[i - 1][j] + other[i - 1][j + 1] +
                     other[i + 1][j - 1] + other[i + 1][j] + other[i + 1][j + 1] + other[i][j]) / 9;
        }
    }
    //handling edges
    image[0][0] = (other[0][1] + other[1][1] + other[1][0] + other[0][0]) / 4;
    image[0][255] = (other[0][254] + other[1][255] + other[1][254] + other[0][255]) / 4;
    image[255][0] = (other[255][0] + other[255][1] + other[254][0] + other[254][1]) / 4;
    image[255][255] = (other[255][255] + other[255][254] + other[254][255] + other[254][254]) / 4;


    for (int j = 1; j < SIZE - 1; ++j) {
        //handling the rest of the array
        image[0][j] =
                (other[1][j + 1] + other[0][j - 1] + other[0][j + 1] + other[0][j] + other[1][j - 1] + other[1][j]) / 6;
        image[j][0] =
                (other[1 + j][1] + other[j - 1][0] + other[j + 1][0] + other[j][0] + other[j - 1][1] + other[j][1]) / 6;
        image[255][j] = (other[254][j + 1] + other[255][j - 1] + other[255][j + 1] + other[255][j] + other[254][j - 1] +
                         other[254][j]) / 6;
        image[j][255] = (other[1 + j][254] + other[j - 1][255] + other[j + 1][255] + other[j][255] + other[j - 1][254] +
                         other[j][254]) / 6;
    }
}


void EnlargeImage() {
    unsigned char other[SIZE][SIZE];
    cout << "Which quarter to enlarge 1, 2, 3 or 4?";
    int n;
    cin >> n;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            other[i][j] = image[i][j];
        }
    }
//put every pixel of the quarter the user want to enlarge in the 4 pixels, the pixel it self and the other 3 surrounding it
    if (n == 1) {
        int k = 0, y = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[y][k] = other[i][j];
                image[y + 1][k] = other[i][j];
                image[y + 1][k + 1] = other[i][j];
                image[y][k + 1] = other[i][j];
                k += 2;
            }
            k = 0;
            y += 2;
        }
    } else if (n == 2) {
        int k = 0, y = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[y][k] = other[i][j];
                image[y + 1][k] = other[i][j];
                image[y + 1][k + 1] = other[i][j];
                image[y][k + 1] = other[i][j];
                k += 2;
            }
            k = 0;
            y += 2;
        }
    } else if (n == 3) {
        int k = 0, y = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[y][k] = other[i][j];
                image[y + 1][k] = other[i][j];
                image[y + 1][k + 1] = other[i][j];
                image[y][k + 1] = other[i][j];
                k += 2;
            }
            k = 0;
            y += 2;
        }
    } else if (n == 4) {
        int k = 0, y = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[y][k] = other[i][j];
                image[y + 1][k] = other[i][j];
                image[y + 1][k + 1] = other[i][j];
                image[y][k + 1] = other[i][j];
                k += 2;
            }
            k = 0;
            y += 2;
        }
    }
}


void shrink() {
    //skipping rows and columns to shrink the photo to the size the user wants
    unsigned char other[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            other[i][j] = image[i][j];
            image[i][j] = 255;
        }
    }
    cout << "Shrink to (1/2), (1/3) or (1/4)?";
    string s;
    cin >> s;
    if (s == "1/2") {
        int a = 0;
        int b = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[i][j] = other[a][b];
                b += 2;
            }
            b = 0;
            a += 2;
        }

    } else if (s == "1/3") {
        int a = 0;
        int b = 0;
        for (int i = 0; i < SIZE / 3; ++i) {
            for (int j = 0; j < SIZE / 3; ++j) {
                image[i][j] = other[a][b];
                b += 3;
            }
            b = 0;
            a += 3;
        }
    } else if (s == "1/4") {
        int a = 0;
        int b = 0;
        for (int i = 0; i < SIZE / 4; ++i) {
            for (int j = 0; j < SIZE / 4; ++j) {
                image[i][j] = other[a][b];
                b += 4;
            }
            b = 0;
            a += 4;
        }
    }
}

void SkewRight() {
    double degree;
    unsigned char shrinkedimage[SIZE][SIZE];
    cout << "Enter degree";
    cin >> degree;
    degree = (degree * 22) / (180 * 7);
    int x = (256 / (1 + (1 / tan(degree))));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            shrinkedimage[i][(j * x) / SIZE] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255;
        }
    }
    double begin = SIZE - x;
    double step = begin / SIZE;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = int(begin); j < begin + x; ++j) {
            image[i][j] = shrinkedimage[i][int(j - begin)];

        }
        begin -= step;
    }
}

void SkewUp() {
    double degree;
    unsigned char shrinkedimage[SIZE][SIZE];
    cout << "Enter degree";
    cin >> degree;
    degree = (degree * 22) / (180 * 7);
    int x = (256 / (1 + (1 / tan(degree))));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            shrinkedimage[(j * x) / SIZE][i] = image[j][i];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255;
        }
    }
    double begin = SIZE - x;
    double step = begin / SIZE;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = int(begin); j < begin + x; ++j) {
            image[j][i] = shrinkedimage[int(j - begin)][i];

        }
        begin -= step;
    }
}


void shuffle() {
    unsigned char other[SIZE][SIZE];
    cout << "New order of quarters ? ";
    int a, b, c, d;
    cin >> a;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            other[i][j] = image[i][j];
        }
    }
    if (a == 2) {
        int a = 0, b = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = 0;
        }
    } else if (a == 3) {
        int a = 0, b = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = 0;
        }
    } else if (a == 4) {
        int a = 0, b = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = 0;
        }
    }
    cin >> b;
    if (b == 1) {
        int a = 0, b = SIZE / 2;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    } else if (b == 3) {
        int a = 0, b = SIZE / 2;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    } else if (b == 4) {
        int a = 0, b = SIZE / 2;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    }
    cin >> c;
    if (c == 1) {
        int a = SIZE / 2, b = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = 0;
        }
    } else if (c == 2) {
        int a = SIZE / 2, b = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = 0;
        }
    } else if (c == 4) {
        int a = SIZE / 2, b = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = 0;
        }
    }
    cin >> d;
    if (d == 1) {
        int a = SIZE / 2, b = SIZE / 2;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    } else if (d == 2) {
        int a = SIZE / 2, b = SIZE / 2;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    } else if (d == 3) {
        int a = SIZE / 2, b = SIZE / 2;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[a][b] = other[i][j];
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    }
}

int main() {
    cout << "Enter your name please" << "\n";
    string user_name;
    cin >> user_name;
    cout << "Hello " << user_name << "\n";
    re:;

    cout << "Chose the number of filter you would like to apply or enter 0 to exit" << "\n"
         << "1-black_and_WhiteFilter\n"
            "2-InvertImage\n"
            "3-MergeImages\n"
            "4-FlipImage\n"
            "5-DarkenAndLighten\n"
            "6-Mirror\n"
            "7-Rotate\n"
            "8-crop\n"
            "9-DetectImageEdges\n"
            "10-blur\n"
            "11-shrink\n"
            "12-EnlargeImage\n"
            "13-SkewRight\n"
            "14-SkewUp\n"
            "15-Shuffle\n";
    int ord;
    cin >> ord;

    if (ord) { //decied filter based on user input
        switch (ord) {
            case 1:
                loadImage();
                black_and_WhiteFilter();
                saveImage();
                goto re;
            case 2:
                loadImage();
                InvertImage();
                saveImage();
                goto re;
            case 3:
                loadImage();
                MergeImages();
                saveImage();
                goto re;
            case 4:
                loadImage();
                FlipImage();
                saveImage();
                goto re;
            case 5:
                loadImage();
                DarkenAndLighten();
                saveImage();
                goto re;
            case 6:
                loadImage();
                Mirror();
                saveImage();
                goto re;
            case 7:
                loadImage();
                Rotate();
                saveImage();
                goto re;
            case 8:
                loadImage();
                crop();
                saveImage();
                goto re;
            case 9:
                loadImage();
                DetectImageEdges();
                saveImage();
                goto re;
            case 10:
                loadImage();
                blur();
                saveImage();
                goto re;
            case 11:
                loadImage();
                shrink();
                saveImage();
                goto re;
            case 12:
                loadImage();
                EnlargeImage();
                saveImage();
                goto re;
            case 13:
                loadImage();
                SkewRight();
                saveImage();
                goto re;
            case 14:
                loadImage();
                SkewUp();
                saveImage();
                goto re;
            case 15:
                loadImage();
                shuffle();
                saveImage();
                goto re;
        }
    }
}





