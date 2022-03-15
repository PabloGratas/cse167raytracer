#include "glm-0.9.7.1/glm/vec3.hpp"

typedef glm::vec3 point;
class Triangle{
    public: 
        point a;
        point b;
        point c;
        glm::vec3 ambient;
        glm::vec3 directionala;
        glm::vec3 directionalb;
        glm::vec3 pointa;
        glm::vec3 pointb;
        glm::vec3 diffuse;
        glm::vec3 specular;
        Triangle(point ap, point bp, point cp);
        ~Triangle();
};