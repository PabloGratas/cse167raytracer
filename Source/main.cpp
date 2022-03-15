
#include <iostream>
#include <Camera.h>
#include "FreeImage.h"
#include "readfile.h"
#include "Scene.h"

using namespace std ;

int main ( int argc, char* argv[] ) {
    
    FreeImage_Initialise();
    const char* filename = argv[1];
    FIBITMAP* bitmap;
    vector<Camera> cams = readmyfile(filename);
    for(auto itr = cams.begin(); itr < cams.end(); itr++){
        bitmap = itr->bitmapBuild();
        //FOR TEST we will need to 
        if(FreeImage_Save(FIF_PNG, bitmap , "image1.png", 0 )) {
            cout << "Image successfully saved!" << endl ;
        }
    }
    FreeImage_DeInitialise(); 
}