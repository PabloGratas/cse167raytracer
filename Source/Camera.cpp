#include <Math.h>
#include "glm-0.9.7.1/glm/vec3.hpp"
#include "glm-0.9.7.1/glm/glm.hpp"
#include "glm-0.9.7.1/glm/gtc/matrix_transform.hpp"
#include "Camera.h"


Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fovy, Scene* scene) {
    w = glm::normalize(lookFrom-lookAt);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);
    thisScene = scene;
    fovy = glm::radians(fovy);
    fovx = tan(fovy/2) * (thisScene->width/thisScene->height);
    fovx = 2 * atan(fovx);
    triList = thisScene->triList;
    sphereList = thisScene->sphereList;
}

Ray Camera::RayThruPixel(int pixelX, int pixelY) {
    //not sure about alpha and beta!!
    float width = thisScene->width;
    float height = thisScene->height;
    float alpha = 2.0*(pixelX+0.5)/width - 1;
    float beta = 1-2.0*(pixelY+0.5)/height;
    vec3 direction = normalize(alpha*u + beta*v - w);
    return Ray(lookFrom, direction);
}

Intersection Camera::sphereIntersect(Ray* pixelRay, Sphere* curObj){ //We need sphere and triangle objects
    Intersection retval = Intersection(point(), vec3(), INFINITY);
    vec3 d = pixelRay->direction;
    point p0 = pixelRay->origin;
    point c = curObj->center;
    float r = curObj->rad;
    float innersqrt =  dot(d,(p0-c))*dot(d,(p0-c))-length(p0-c)*length(p0-c)+r*r;
    if(innersqrt <= 0) return retval;
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

Intersection Camera::triangleIntersect(Ray* pixelRay, Triangle* curObj){
    //not 100% sure about
    Intersection retval = Intersection(point(), vec3(), INFINITY);
    vec3 A = curObj->a;
    vec3 B = curObj->b;
    vec3 C = curObj->c;
    vec3 CminusA = curObj->c - curObj->a;
    vec3 BminusA = curObj->b - curObj->a;
    vec3 normal = glm::normalize(glm::cross(CminusA, BminusA));
    float t = (glm::dot(A, normal) - glm::dot(pixelRay->origin, normal)) / glm::dot(pixelRay->direction, normal);
    //check if point is behind triangle
    if (t <= 0) {
        return retval;
    }
    else {
        vec3 P = pixelRay->origin + t * pixelRay->direction;
        //check if Point is inside the triangle
        
        vec3 PminusA = P - A;
        vec3 PminusB = P - B;
        vec3 PminusC = P - C;
        vec3 CminusB = curObj->c - curObj->b;
        vec3 AminusC = curObj->a - curObj->c;

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

Intersection Camera::Intersect(Ray* pixelRay){
    Intersection retval = Intersection(point(), vec3(), INFINITY);
    float minDist = INFINITY;
    float curDist;
    Intersection curInter = Intersection(point(), vec3(), INFINITY);
    for(auto itr = sphereList.begin(); itr != sphereList.end(); itr++){
        curInter = sphereIntersect(pixelRay, &*itr);
        curDist = curInter.dist;
        if(curDist < 0) continue;
        if(curDist < minDist){
            minDist = curDist;
            retval = curInter;
        }
    }
    /*for(auto itr = triList.begin(); itr != triList.end(); itr++){
        curInter = triangleIntersect(pixelRay, &*itr);
        curDist = curInter.dist;
        if(curDist < 0) continue;
        if(curDist < minDist){
            minDist = curDist;
            retval = curInter;
        }
    }*/
    //Return the Intersect with the shortest distance
    return retval;
}

FIBITMAP* Camera::bitmapBuild(){
    FIBITMAP* bitmap = FreeImage_Allocate(thisScene->width, thisScene->height, 24);
    RGBQUAD color;
    if (!bitmap) {
        exit (1);
    }
    for(int x = 0; x < thisScene->width; x++){
        for(int y = 0; y < thisScene->height; y++){
            //Get a ray, plug it into the intersection function. If we get a valid intersect, render red.
            //printf("Pixel (%d, %d)\n", x, y); //Progress indicator
            Ray cur = RayThruPixel(x, y);
            Intersection curInter = Intersect(&cur);
            if(curInter.dist == INFINITY || curInter.dist < 0){
                color.rgbRed = 0;
                color.rgbBlue = 0;
                color.rgbGreen = 0;
                FreeImage_SetPixelColor(bitmap, x, y, &color);
            } else {
                color.rgbRed = 0.0;
                color.rgbGreen = 0.0;
                color.rgbBlue = 255.0;
                FreeImage_SetPixelColor(bitmap, x, y, &color);
            }
        }
    }
    return bitmap;
}

