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




