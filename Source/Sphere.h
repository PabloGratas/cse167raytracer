#include "glm-0.9.7.1/glm/vec3.hpp"

typedef glm::vec3 point;
class Sphere{
    public: 
        point center; //Center of the sphere.
        float rad; //Radius of the sphere.
        Sphere(point center, float rad);
        ~Sphere();
};