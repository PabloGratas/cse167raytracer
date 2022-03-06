#include <Math.h>
#include "glm-0.9.7.1/glm/vec3.hpp"
#include "glm-0.9.7.1/glm/glm.hpp"
#include "glm-0.9.7.1/glm/gtc/matrix_transform.hpp"
#include "Camera.h"


Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fovy, Scene scene) {
    w = glm::normalize(lookFrom-lookAt);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);
    fovy = glm::radians(fovy);
    fovx = tan(fovy/2) * (scene.width/scene.height);
    fovx = 2 * atan(fovx);
}

Ray Camera::RayThruPixel(int pixelX, int pixelY, Scene scene) {
    //not sure about alpha and beta!!
    int halfSceneWidth = scene.width/2;
    int halfSceneHeight = scene.height/2;

    float pixX = pixelX + 0.5;
    float pixY = pixelY + 0.5;

    float alpha = tan(fovx/2)*((pixY-halfSceneWidth)/halfSceneWidth)+0.5;
    float beta = tan(fovy/2)*((halfSceneHeight-pixX)/halfSceneHeight)+0.5;
    vec3 direction = normalize(alpha*u + beta*u - w);
    return Ray(lookFrom, direction);
}

Intersection sphereIntersect(Ray pixelRay, Sphere curObj){ //We need sphere and triangle objects
    
}
Intersection triangleIntersect(Ray pixelRay, Triangle curObj){
    //Triangle hit logic
    //if hit return correct Intersection else return intersection with dist set to infinity
}

Intersection Intersect(Ray pixelRay, Scene scene){
    Intersection retInter;
    float minDist = INFINITY;
    float curDist;
    Intersection curInter;
    for(auto itr = scene.sphereList.begin(); itr < scene.sphereList.end(); itr++){
        curInter = sphereIntersect(pixelRay, *itr);
        curDist = curInter.dist;
        if(curDist < minDist){
            minDist = curDist;
            retInter = curInter;
        }
    }
    for(auto itr = scene.triList.begin(); itr < scene.triList.end(); itr++){
        curInter = triangleIntersect(pixelRay, *itr);
        curDist = curInter.dist;
        if(curDist < minDist){
            minDist = curDist;
            retInter = curInter;
        }
    }
    //Return the Intersect with the shortest distance
    return retInter;
}

