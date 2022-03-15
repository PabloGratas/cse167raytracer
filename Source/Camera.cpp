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
    Intersection retval = Intersection(point(), vec3(), INFINITY);
    vec3 d = pixelRay.direction;
    point p0 = pixelRay.origin;
    point c = curObj.center;
    float r = curObj.rad;
    float innersqrt =  dot(d,(p0-c))*dot(d,(p0-c))-length(p0-c)*length(p0-c)+r*r;
    float tplus = dot(-d,(p0 - c))+sqrt(innersqrt);
    float tminus = dot(-d,(p0 - c))-sqrt(innersqrt);
    if(innersqrt > 0){
        if(tminus > 0){
            retval.pos = p0 + tminus*d;
            retval.surNorm = normalize(retval.pos-c);
            retval.dist = tminus;
        } else if (tplus > 0){
            retval.pos = p0 + tplus*d;
            retval.surNorm = normalize(retval.pos-c);
            retval.dist = tplus;
        }
    } 
    return retval;
}
Intersection triangleIntersect(Ray pixelRay, Triangle curObj){
    //not 100% sure about
    Intersection retval = Intersection(point(), vec3(), INFINITY);
    vec3 A = curObj.a;
    vec3 B = curObj.b;
    vec3 C = curObj.c;
    vec3 CminusA = curObj.c - curObj.a;
    vec3 BminusA = curObj.b - curObj.a;
    vec3 normal = glm::normalize(glm::cross(CminusA, BminusA));
    float t = (glm::dot(A, normal) - glm::dot(pixelRay.origin, normal)) / glm::dot(pixelRay.direction, normal);

    //check if point is behind triangle
    if (t < 0) {
        return retval;
    }
    else {
        vec3 P = pixelRay.origin + t * pixelRay.direction;
        //check if Point is inside the triangle
        
        vec3 PminusA = P - A;
        vec3 PminusB = P - B;
        vec3 PminusC = P - C;
        vec3 CminusB = curObj.c - curObj.b;
        vec3 AminusC = curObj.a - curObj.c;

        bool inTriangle = false;
        if (glm::dot(glm::cross(BminusA, PminusA), normal) >= 0) {
            if (glm::dot(glm::cross(CminusB, PminusB), normal) >= 0) {
                if (glm::dot(glm::cross(BminusA, PminusA), normal) >= 0) {
                    inTriangle = true;
                }
                else {return retval;} 
            }
            else {return retval;} 
        }

        else {return retval;} 

        if (inTriangle == true) {
            retval.pos = P;
            retval.surNorm = normal;
            retval.dist = t;
            return retval;
        }
        else {return retval;}

    }
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

