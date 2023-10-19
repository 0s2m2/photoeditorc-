#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];

void loadImage() {
    char imageFileName[100];

    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}


void saveImage() {
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

void black_and_WhiteFilter() {
    //all pixels higher than 127 totally white and any other totally black
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3 > 127) {
                image[i][j][0] = 255;
                image[i][j][1] = 255;
                image[i][j][2] = 255;
            } else {
                image[i][j][0] = 0;
                image[i][j][1] = 0;
                image[i][j][2] = 0;
            }


        }
    }
}

void InvertImage() {
    //just inverting color by subtract the pixel from 255
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {


                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}

void MergeImages() {
    //takes the average of every pixel with the other pixel in the other photo
    char otherimageFileName[100];
    unsigned char result[SIZE][SIZE][RGB];
    unsigned char otherimage[SIZE][SIZE][RGB];

    cout << "Please enter name of image file to merge with: ";
    cin >> otherimageFileName;

    strcat(otherimageFileName, ".bmp");
    readRGBBMP(otherimageFileName, otherimage);
    char resFileName[100];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {


                result[i][j][k] = (image[i][j][k] + otherimage[i][j][k]) / 2;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {


                image[i][j][k] = result[i][j][k];
            }
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
                for (int k = 0; k < RGB; ++k) {


                    int temp;
                    temp = image[i][j][k];
                    image[i][j][k] = image[i][255 - j][k];
                    image[i][255 - j][k] = temp;

                }
            }
        }
    } else if (c == 'v') {
        //switching horizontal pixels to flip vertically
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {


                    int temp;
                    temp = image[j][i][k];
                    image[j][i][k] = image[255 - j][i][k];
                    image[255 - j][i][k] = temp;
                }
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
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[i][j][k] / 2;
                }
            }
        }
    } else if (c == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {


                    image[i][j][k] = image[i][j][k] + (255 - image[i][j][k]) / 2;
                }
            }
        }
    }
}

void shrink() {
    //skipping rows and columns to shrink the photo to the size the user wants
    unsigned char other[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {


                other[i][j][k] = image[i][j][k];
                image[i][j][k] = 255;
            }
        }
    }
    cout << "Shrink to (1/2), (1/3) or (1/4)?";
    string s;
    cin >> s;
    if (s == "1/2") {

        int b = 0;
        for (int k = 0; k < RGB; ++k) {
            int a = 0;
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    image[i][j][k] = other[a][b][k];
                    b += 2;
                }
                b = 0;
                a += 2;
            }


        }

    } else if (s == "1/3") {
        int b = 0;
        for (int k = 0; k < RGB; ++k) {
            int a = 0;
            for (int i = 0; i < SIZE / 3; ++i) {
                for (int j = 0; j < SIZE / 3; ++j) {
                    image[i][j][k] = other[a][b][k];
                    b += 3;
                }
                b = 0;
                a += 3;
            }


        }


    } else if (s == "1/4") {

        int b = 0;
        for (int k = 0; k < RGB; ++k) {
            int a = 0;
            for (int i = 0; i < SIZE / 4; ++i) {
                for (int j = 0; j < SIZE / 4; ++j) {
                    image[i][j][k] = other[a][b][k];
                    b += 4;
                }
                b = 0;
                a += 4;
            }
        }
    }
}

void EnlargeImage() {
    unsigned char other[SIZE][SIZE][RGB];
    cout << "Which quarter to enlarge 1, 2, 3 or 4?";
    int n;
    cin >> n;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                other[i][j][k] = image[i][j][k];
            }
        }
    }
//put every pixel of the quarter the user want to enlarge in the 4 pixels, the pixel it self and the other 3 surrounding it
    if (n == 1) {
        int k = 0, y = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int l = 0; l < RGB; ++l) {
                    image[y][k][l] = other[i][j][l];
                    image[y + 1][k][l] = other[i][j][l];
                    image[y + 1][k + 1][l] = other[i][j][l];
                    image[y][k + 1][l] = other[i][j][l];
                }
                k += 2;
            }
            k = 0;
            y += 2;
        }
    } else if (n == 2) {
        int k = 0, y = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                for (int l = 0; l < RGB; ++l) {
                    image[y][k][l] = other[i][j][l];
                    image[y + 1][k][l] = other[i][j][l];
                    image[y + 1][k + 1][l] = other[i][j][l];
                    image[y][k + 1][l] = other[i][j][l];
                }
                k += 2;
            }
            k = 0;
            y += 2;
        }
    } else if (n == 3) {
        int k = 0, y = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; j++) {
                for (int l = 0; l < RGB; ++l) {
                    image[y][k][l] = other[i][j][l];
                    image[y + 1][k][l] = other[i][j][l];
                    image[y + 1][k + 1][l] = other[i][j][l];
                    image[y][k + 1][l] = other[i][j][l];
                }
                k += 2;
            }
            k = 0;
            y += 2;
        }
    } else if (n == 4) {
        int k = 0, y = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                for (int l = 0; l < RGB; ++l) {
                    image[y][k][l] = other[i][j][l];
                    image[y + 1][k][l] = other[i][j][l];
                    image[y + 1][k + 1][l] = other[i][j][l];
                    image[y][k + 1][l] = other[i][j][l];
                }
                k += 2;
            }
            k = 0;
            y += 2;
        }
    }
}


void shuffle() {
    unsigned char other[SIZE][SIZE][RGB];
    cout << "New order of quarters ? ";
    int a, b, c, d;
    cin >> a;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                other[i][j][k] = image[i][j][k];
            }
        }
    }
    if (a == 2) {
        int a = 0, b = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = 0;
        }
    } else if (a == 3) {
        int a = 0, b = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = 0;
        }
    } else if (a == 4) {
        int a = 0, b = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
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
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    } else if (b == 3) {
        int a = 0, b = SIZE / 2;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    } else if (b == 4) {
        int a = 0, b = SIZE / 2;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
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
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = 0;
        }
    } else if (c == 2) {
        int a = SIZE / 2, b = 0;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = 0;
        }
    } else if (c == 4) {
        int a = SIZE / 2, b = 0;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
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
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    } else if (d == 2) {
        int a = SIZE / 2, b = SIZE / 2;
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    } else if (d == 3) {
        int a = SIZE / 2, b = SIZE / 2;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[a][b][k] = other[i][j][k];
                }
                b++;
            }
            a++;
            b = SIZE / 2;
        }
    }
}

void Rotate() {
    unsigned char other[SIZE][SIZE][RGB];
    int x;
    cout << "Rotate (90), (180) or (270) degrees?";
    cin >> x;
    if (x == 90) {
        for (int i = SIZE - 1; i >= 0; --i) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    other[j][i][k] = image[SIZE - i - 1][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = other[i][j][k];
                }
            }
        }
    } else if (x == 180) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[i][255 - j][k];
                    image[i][255 - j][k] = temp;
                }

            }
        }
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[255 - i][j][k];
                    image[255 - i][j][k] = temp;
                }
            }
        }
    } else if (x == 270) {
        for (int i = SIZE - 1; i >= 0; --i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[j][i][k] = image[SIZE - i - 1][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = other[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[i][255 - j][k];
                    image[i][255 - j][k] = temp;
                }
            }
        }
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[255 - i][j][k];
                    image[255 - i][j][k] = temp;
                }
            }
        }
    }
}

void DetectImageEdges() {
    unsigned char other[SIZE][SIZE][RGB];
    black_and_WhiteFilter(); // turn image into b&w
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            for (int k = 0; k < RGB; ++k) {
                if ((image[i + 1][j][0] + image[i + 1][j][1] + image[i + 1][j][2]) / 3 !=
                    (image[i - 1][j][0] + image[i - 1][j][1] + image[i - 1][j][2]) / 3 ||
                    (image[i][j + 1][0] + image[i][j + 1][1] + image[i][j + 1][2]) / 3 !=
                    (image[i][j - 1][0] + image[i][j - 1][1] + image[i][j - 1][2]) / 3) {
                    other[i][j][k] = 0; // لو البيكسل اللي فوقيها لا تساوي اللي تحتيها او البيكسل اللي علي يمينها لا تساوي اللي علي يسارها هتبقي لونها اسود
                } else {
                    other[i][j][k] = 255; // غير كده هيبقي لونها ابيض
                }
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = other[i][j][k];
            }
        }
    }
}

void Mirror() {
    unsigned char other[SIZE][SIZE][RGB];
    char s;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?";
    cin >> s;
    if (s == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[i][j][k] = image[i][j][k]; // هنعمل نسخ للصورة لحد نص ال coulmns
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) { // هنعمل flip horizontal
                for (int k = 0; k < RGB; ++k) {
                    int temp;
                    temp = image[i][j][k];
                    image[i][j][k] = image[i][255 - j][k];
                    image[i][255 - j][k] = temp;
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) { // هنعمل نسخ لباقي الصورة من الصور الل عكسناها
            for (int j = 127; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[i][j][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = other[i][j][k];
                }
            }
        }
    } else if (s == 'r') {
        for (int i = 0; i < SIZE; ++i) { // نفس فكرة اللي قبلها
            for (int j = 127; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[i][j][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    int temp;
                    temp = image[i][j][k];
                    image[i][j][k] = image[i][255 - j][k];
                    image[i][255 - j][k] = temp;
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[i][j][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = other[i][j][k];
                }
            }
        }
    } else if (s == 'u') {
        for (int i = 0; i < SIZE / 2; ++i) { // نفس فكرة اللي قبلها بس هنعمل flip vertical
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[i][j][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    int temp;
                    temp = image[j][i][k];
                    image[j][i][k] = image[255 - j][i][k];
                    image[255 - j][i][k] = temp;
                }
            }
        }
        for (int i = 127; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[i][j][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k)
                    image[i][j][k] = other[i][j][k];
            }
        }
    } else if (s == 'd') {
        for (int i = 127; i < SIZE; ++i) { // نفس فكرة اللي قبلها
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[i][j][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    int temp;
                    temp = image[j][i][k];
                    image[j][i][k] = image[255 - j][i][k];
                    image[255 - j][i][k] = temp;
                }
            }
        }
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    other[i][j][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = other[i][j][k];
                }
            }
        }
    }
}

void crop() {
    unsigned char other[SIZE][SIZE][RGB];
    int x, y, w, l;
    cout << "Please enter x y l w: ";
    cin >> x >> y >> l >> w;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                other[i][j][k] = 255;  // عملنا صورة بيضاء اللون
            }
        }
    }
    for (int i = x; i < l + x; ++i) {
        for (int j = y; j < w + y; ++j) {
            for (int k = 0; k < RGB; ++k) {
                other[i][j][k] = image[i][j][k]; // هنملي الصورة علي حسب الابعاد اللي المستخدم هيحطها من الصورةالاصلية وهنسيب الباقي ابيض
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = other[i][j][k];
            }
        }
    }
}

void blur() {
    unsigned char other[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                other[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] =
                        (other[i][j + 1][k] + other[i][j - 1][k] + other[i - 1][j - 1][k] + other[i - 1][j][k] +
                         other[i - 1][j + 1][k] +
                         other[i + 1][j - 1][k] + other[i + 1][j][k] + other[i + 1][j + 1][k] + other[i][j][k]) / 9;
            }
        }
    }
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] =
                        (other[i][j + 1][k] + other[i][j - 1][k] + other[i - 1][j - 1][k] + other[i - 1][j][k] +
                         other[i - 1][j + 1][k] +
                         other[i + 1][j - 1][k] + other[i + 1][j][k] + other[i + 1][j + 1][k] + other[i][j][k]) / 9;
            }
        }
    }
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] =
                        (other[i][j + 1][k] + other[i][j - 1][k] + other[i - 1][j - 1][k] + other[i - 1][j][k] +
                         other[i - 1][j + 1][k] +
                         other[i + 1][j - 1][k] + other[i + 1][j][k] + other[i + 1][j + 1][k] + other[i][j][k]) / 9;
            }
        }
    }
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] =
                        (other[i][j + 1][k] + other[i][j - 1][k] + other[i - 1][j - 1][k] + other[i - 1][j][k] +
                         other[i - 1][j + 1][k] +
                         other[i + 1][j - 1][k] + other[i + 1][j][k] + other[i + 1][j + 1][k] + other[i][j][k]) / 9;
            }
        }
    }
    //handling edges
    image[0][0][0] = (other[0][1][0] + other[1][1][0] + other[1][0][0] + other[0][0][0]) / 4;
    image[0][255][0] = (other[0][254][0] + other[1][255][0] + other[1][254][0] + other[0][255][0]) / 4;
    image[255][0][0] = (other[255][0][0] + other[255][1][0] + other[254][0][0] + other[254][1][0]) / 4;
    image[255][255][0] = (other[255][255][0] + other[255][254][0] + other[254][255][0] + other[254][254][0]) / 4;
    image[0][0][1] = (other[0][1][1] + other[1][1][1] + other[1][0][1] + other[0][0][1]) / 4;
    image[0][255][1] = (other[0][254][1] + other[1][255][1] + other[1][254][1] + other[0][255][1]) / 4;
    image[255][0][1] = (other[255][0][1] + other[255][1][1] + other[254][0][1] + other[254][1][1]) / 4;
    image[255][255][1] = (other[255][255][1] + other[255][254][1] + other[254][255][1] + other[254][254][1]) / 4;
    image[0][0][2] = (other[0][1][2] + other[1][1][2] + other[1][0][2] + other[0][0][2]) / 4;
    image[0][255][2] = (other[0][254][2] + other[1][255][2] + other[1][254][2] + other[0][255][2]) / 4;
    image[255][0][2] = (other[255][0][2] + other[255][1][2] + other[254][0][2] + other[254][1][2]) / 4;
    image[255][255][2] = (other[255][255][2] + other[255][254][2] + other[254][255][2] + other[254][254][2]) / 4;

    for (int j = 1; j < SIZE - 1; ++j) {
        for (int i = 0; i < RGB; ++i) {
            //handling the rest of the array
            image[0][j][i] =
                    (other[1][j + 1][i] + other[0][j - 1][i] + other[0][j + 1][i] + other[0][j][i] +
                     other[1][j - 1][i] + other[1][j][i]) / 6;
            image[j][0][i] =
                    (other[1 + j][1][i] + other[j - 1][0][i] + other[j + 1][0][i] + other[j][0][i] +
                     other[j - 1][1][i] + other[j][1][i]) / 6;
            image[255][j][i] = (other[254][j + 1][i] + other[255][j - 1][i] + other[255][j + 1][i] + other[255][j][i] +
                                other[254][j - 1][i] +
                                other[254][j][i]) / 6;
            image[j][255][i] = (other[1 + j][254][i] + other[j - 1][255][i] + other[j + 1][255][i] + other[j][255][i] +
                                other[j - 1][254][i] +
                                other[j][254][i]) / 6;
        }
    }
}

void SkewRight() {
    double degree;
    unsigned char shrinkedimage[SIZE][SIZE][RGB];
    cout << "Enter degree";
    cin >> degree;
    degree = (degree * 22) / (180 * 7);
    int x = (256 / (1 + (1 / tan(degree))));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            shrinkedimage[i][(j * x) / SIZE][0] = image[i][j][0];
            shrinkedimage[i][(j * x) / SIZE][1] = image[i][j][1];
            shrinkedimage[i][(j * x) / SIZE][2] = image[i][j][2];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255;

            }

        }

    }

    double begin = SIZE - x;
    double step = begin / SIZE;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = int(begin); j < begin + x; ++j) {
            image[i][j][0] = shrinkedimage[i][int(j - begin)][0];
            image[i][j][1] = shrinkedimage[i][int(j - begin)][1];
            image[i][j][2] = shrinkedimage[i][int(j - begin)][2];

        }
        begin -= step;
    }

}

void SkewUp() {

    double degree;
    unsigned char shrinkedimage[SIZE][SIZE][RGB];
    cout << "Enter degree";
    cin >> degree;
    degree = (degree * 22) / (180 * 7);
    int x = (256 / (1 + (1 / tan(degree))));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            shrinkedimage[(j * x) / SIZE][i][0] = image[j][i][0];
            shrinkedimage[(j * x) / SIZE][i][1] = image[j][i][1];
            shrinkedimage[(j * x) / SIZE][i][2] = image[j][i][2];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255;

            }

        }

    }

    double begin = SIZE - x;
    double step = begin / SIZE;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = int(begin); j < begin + x; ++j) {
            image[j][i][0] = shrinkedimage[int(j - begin)][i][0];
            image[j][i][1] = shrinkedimage[int(j - begin)][i][1];
            image[j][i][2] = shrinkedimage[int(j - begin)][i][2];

        }
        begin -= step;
    }

}

int main() {
    cout << "Enter your name please" << "\n";
    string user_name;
    cin >> user_name;
    cout << "Hello " << user_name << "\n";
    char n = 'a';
    loadImage();
    while (n != '0') {
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
                "15-Shuffle\n"
                "16-save\n";
        int n;
        cin >> n;
        switch (n) {
            case 1:
                //loadImage();
                black_and_WhiteFilter();
                //saveImage();
                break;
            case 2:
                // loadImage();
                InvertImage();
                // saveImage();
                break;
            case 3:
                // loadImage();
                MergeImages();
                //saveImage();
                break;
            case 4:
                // loadImage();
                FlipImage();
                //saveImage();
                break;
            case 5:
                // loadImage();
                DarkenAndLighten();
                //saveImage();
                break;
            case 6:
                // loadImage();
                Mirror();
                //saveImage();
                break;
            case 7:
                // loadImage();
                Rotate();
                //saveImage();
                break;
            case 8:
                //  loadImage();
                crop();
                //saveImage();
                break;
            case 9:
                //  loadImage();
                DetectImageEdges();
                //saveImage();
                break;
            case 10:
                //  loadImage();
                blur();
                //saveImage();
                break;
            case 11:
                //  loadImage();
                shrink();
                //saveImage();
                break;
            case 12:
                //  loadImage();
                EnlargeImage();
                // saveImage();
                break;
            case 13:
                //  loadImage();
                SkewRight();
                //saveImage();
                break;
            case 14:
                //  loadImage();
                SkewUp();
                // saveImage();
                break;
            case 15:
                //  loadImage();
                shuffle();
                //saveImage();
                break;
            case 16 :
                saveImage();
                break;
            case 0 :
                return 0;
            default:
                break;
        }
    }
}