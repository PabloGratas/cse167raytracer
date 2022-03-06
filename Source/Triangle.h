#include "glm-0.9.7.1/glm/vec3.hpp"

typedef glm::vec3 point;
class Triangle{
    public: 
        point a;
        point b;
        point c;
        Triangle(point a, point b, point c);
        ~Triangle();
};