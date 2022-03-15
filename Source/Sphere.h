#ifndef SPHERE_HEADER
#define SPHERE_HEADER
#include "glm-0.9.7.1/glm/vec3.hpp"

typedef glm::vec3 point;
class Sphere{
    public: 
        point center; //Center of the sphere.
        float rad; //Radius of the sphere.
        glm::vec3 ambient;
        glm::vec3 directionala;
        glm::vec3 directionalb;
        glm::vec3 pointa;
        glm::vec3 pointb;
        glm::vec3 diffuse;
        glm::vec3 specular;
        Sphere(point c, float r);
        ~Sphere();
};
#endif