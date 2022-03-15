#ifndef CAM_HEADER
#define CAM_HEADER
#include "glm-0.9.7.1/glm/vec3.hpp"
#include "Ray.h"
#include "Scene.h"
#include "Intersection.h"
#include "FreeImage.h"
#include "Sphere.h"
#include "Triangle.h"
typedef glm::vec3 vec3 ; 

class Camera {
    
    public:
        Camera();
        FIBITMAP* bitmapBuild();
        Intersection Intersect(Ray* pixelRay);
        Intersection triangleIntersect(Ray* pixelRay, Triangle* curObj);
        Intersection sphereIntersect(Ray* pixelRay, Sphere* curObj);
        Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fovy, Scene* scene);
        //method to generate rays to each pixel 
        Ray RayThruPixel(int pixelX, int pixelY);
        Scene* thisScene;
        vec3 lookFrom;
        vec3 lookAt;
        vec3 up;
        vec3 fov;
        vec3 w;
        vec3 u;
        vec3 v;
        vector<Sphere> sphereList; //list of all our spheres
        vector<Triangle> triList; //list of all our triangles
        float fovy = 45.0;
        float fovx;
};
#endif