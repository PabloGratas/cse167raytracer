#include "glm-0.9.7.1/glm/vec3.hpp"
#include "Triangle.h"
#include "Sphere.h"
typedef glm::vec3 vec3;
typedef glm::vec3 point;
class Intersection { //See page 27 of the ray tracing slides

    public:
        point pos;
        vec3 surNorm;
        vec3 incoming;
        float dist;
        Intersection (point pos, vec3 surNorm, vec3 incoming, float dist);
        Intersection();
        ~Intersection();


};
