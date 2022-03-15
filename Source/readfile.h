#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "glm-0.9.7.1/glm/vec3.hpp"
#include "glm-0.9.7.1/glm/glm.hpp"
#include "glm-0.9.7.1/glm/gtc/matrix_transform.hpp"

using namespace std;
#include "Camera.h"
#include "Scene.h"
#include "Triangle.h"
#include "Sphere.h"
//void matransform (stack<mat4> &transfstack, GLfloat * values) ;
//void rightmultiply (const mat4 & M, stack<mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, float * values) ;
vector<Camera> readmyfile (const char * filename) ;