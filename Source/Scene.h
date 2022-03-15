#ifndef SCENE_HEADER
#define SCENE_HEADER
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
        glm::vec3 ambient;
        glm::vec3 directionala;
        glm::vec3 directionalb;
        glm::vec3 pointa;
        glm::vec3 pointb;
        glm::vec3 diffuse;
        glm::vec3 specular;
        vector<Sphere> sphereList; //list of all our spheres
        vector<Triangle> triList; //list of all our triangles
        Scene(int w, int h);
};
#endif