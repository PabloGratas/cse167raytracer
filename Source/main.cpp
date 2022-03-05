
#include <iostream>
#include "FreeImage.h"
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

#include "Scene.h"

using namespace std ;

//#include "readfile.h"

//method to output image
void saveScreenshot(string fname, int width, int height) {
  int pix = width * height;
  BYTE *pixels = new BYTE[3*pix];	
  glReadBuffer(GL_FRONT);
  glReadPixels(0,0,width,height,GL_BGR,GL_UNSIGNED_BYTE, pixels);

  FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

  std::cout << "Saving screenshot: " << fname << "\n";

  FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
  delete[] pixels;
}

/**
 *  saveScreenshot(string filename, Image image, int image_width, int image_height)
 * {
    BYTE *bytes = image_bytes;
    FIBITMAP *img = FreeImage_ConvertFromRawBits(bytes, width, height, width * 3, 24, 0, 0, 0, true);
    return FreeImage_Save(FIF_PNG, img, fileName.c_str(), 0);
    }
*/

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