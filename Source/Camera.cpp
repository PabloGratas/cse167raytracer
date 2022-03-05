#include "glm.0.9.7.1/build/native/include/glm/vec3.hpp"
#include "Ray.h"
#include "Camera.h"
#include "Image.h"
#include "Readfile.h"
#include "Scene.h"

Camera::Camera() {
    
}

Ray RayThruPixel(w,h){
    glm::vec3 rayVec = glm::vec3(w, h, -1); //(0,0,-1) is what the camera eyenorm is set to.
    Ray retRay = Ray(centerNorm, rayVec); //Ray whos origin is the camera and direction is the generated ray vector.
    return retRay;
}

Image Raytrace(Scene scene){
    int sw = scene.width; int sh = scene.height;
    Image image = new Image(sw, sh); //Generate a new image of the correct size
    for(int h=0; h<sh; h++){ //For every height pos
        for(int w=0; w<sw; w++){ //For every width pos
            Ray ray = RayThruPixel(w, h); //Generate a ray from the pixel at w,h
            Intersection hit = Intersect(ray); //For this ray, return the intersection closest to the origin
            image.pixels[w][h] = FindColor(hit); //Get a color given that intersection and store it in the image array
        }
    }
    return image; //Return the image
}

Intersection Intersect(Ray ray){
    Intersect retVal;
    float dist;
    for(/*list of objects in the scene*/;;){
        switch(/*obj.type*/){
            case sphere: 
                Intersect newVal = sphereIntersect(ray, obj).distance;
                newdist = retVal.dist;
                if(newdist < dist){ //Only update the working object if the object is infront of everything else we've checked so far.
                    dist = newdist;
                    retVal = newVal;
                } 
                break;
            case triangle:
                Intersect newVal = triangleIntersect(ray, obj).distance;
                newdist = retVal.dist;
                if(newdist < dist){
                    dist = newdist;
                    retVal = newVal;
                } 
                break;
            default:
                return nullptr;
        }
    }
    //Return the Intersect with the shortest distance
}

Intersection sphereIntersect(ray, sphere){ //We need sphere and triangle objects
    //Sphere hit logic
    //if hit then return correct Intersection else return intersection with dist set to infinity
}
Intersection triangleIntersect(ray, tri){
    //Triangle hit logic
    //if hit return correct Intersection else return intersection with dist set to infinity
}