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
