#include "glm-0.9.7.1/glm/vec3.hpp"
#include "Ray.h"
#include "Scene.h"
#include "Intersection.h"

typedef glm::vec3 vec3 ; 

class Camera {
    
    public:
        Camera();
        Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fovy, Scene scene);
        //method to generate rays to each pixel 
        void setEye(vec3 eyeInput) {lookFrom = eyeInput;};
        void setlookAt(vec3 lookAtInput) {lookAt = lookAtInput;};
        void setUp(vec3 upInput) {up = upInput;};
        void setfov(float fovInput) {fovy = fovInput;};
        Ray RayThruPixel(int pixelX, int pixY, Scene scene);

    private:
        vec3 lookFrom;
        vec3 lookAt;
        vec3 up;
        vec3 fov;
        vec3 w;
        vec3 u;
        vec3 v;
        float fovy = 45.0;
        float fovx;
};