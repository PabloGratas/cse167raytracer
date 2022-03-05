#include <iostream>
#include "FreeImage.h"
using namespace std;
int main ( int argc, char* argv[] ) {

    FreeImage_Initialise();
    FIBITMAP* bitmap = FreeImage_Allocate(800, 600, 24);
    RGBQUAD color;
    if (!bitmap) {
    exit (1); 
    }
    //FOR TEST we will need to 
    for ( int i =0; i<800; i++) {
        for ( int j =0; j<600; j++) {
            color.rgbRed = 0 ;
            color.rgbGreen = 255.0;
            color.rgbBlue = 255.0;
            FreeImage_SetPixelColor(bitmap, i , j ,& color);

        }
    }
    if(FreeImage_Save(FIF_PNG, bitmap , "test.png", 0 )) {
        cout << "Image successfully saved!" << endl ;
    }
    FreeImage_DeInitialise(); 
}