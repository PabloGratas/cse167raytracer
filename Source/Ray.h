#include "glm.0.9.7.1/build/native/include/glm/vec3.hpp"

class Ray {
    
    //constructor
    Ray(glm::vec3 origin, glm::vec3 t_direction);

    public:
        glm::vec3 origin;
        glm::vec3 t_direction; 
};