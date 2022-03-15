#ifndef IMG_HEADER
#define IMG_HEADER
#include "FreeImage.h"
#include <vector>
using namespace std;
class Image {
    
    const int width ;
    const int height;
    vector<RGBQUAD> pixels;

    public:
        Image (int width, int height);
        ~Image();


};
#endif