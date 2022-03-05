#include "glm.0.9.7.1/build/native/include/glm/vec3.hpp"

class Camera {
    
    public:
        Camera();
        //method to generate rays to each pixel 
    
    
        glm::vec3 eyeNorm = { 0, 0, -1 };
        glm::vec3 centerNorm = { 0, 0, 0 };
        glm::vec3 upNorm = { 0, 1, 0 };
        
        int fovy = 45;
};