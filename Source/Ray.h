#include "glm-0.9.7.1/glm/vec3.hpp"
typedef glm::vec3 vec3;
typedef glm::vec3 point;
class Ray {
    

    public:
        point origin;
        vec3 direction; 
        Ray(point origin, vec3 direction);
        ~Ray();
};