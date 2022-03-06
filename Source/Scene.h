#include "glm-0.9.7.1/glm/vec3.hpp"
#include <vector>
#include "Sphere.h"
#include "Triangle.h"
using namespace std;

class Scene {
    public:
        int width = 0;
        int height = 0; 
        int maxDepth = 5; //Max number of iterations to reflect on
        vector<Sphere> sphereList; //list of all our spheres
        vector<Triangle> triList; //list of all our triangles
        Scene(int width, int height);
        ~Scene();
};