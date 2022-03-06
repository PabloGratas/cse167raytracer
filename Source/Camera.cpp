#include <Math.h>
#include "glm-0.9.7.1/glm/vec3.hpp"
#include "glm-0.9.7.1/glm/glm.hpp"
#include "glm-0.9.7.1/glm/gtc/matrix_transform.hpp"
#include "Camera.h"

Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fovy, Scene scene) {
    w = glm::normalize(lookFrom-lookAt);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);
    fovy = glm::radians(fovy);
    fovx = tan(fovy/2) * (scene.getSceneWidth()/scene.getSceneHeight());
    fovx = 2 * atan(fovx);
}

Ray Camera::RayThruPixel(int pixelX, int pixY, Scene scene) {
    //not sure about alpha and beta!!
    int halfSceneWidth = scene.getSceneWidth()/2;
    int halfSceneHeight = scene.getSceneHeight()/2;
    
    float alpha = tan(fovx/2)*((pixY-halfSceneWidth)/halfSceneWidth);
    float beta = tan(fovy/2)*((halfSceneHeight-pixelX)/halfSceneHeight);
    vec3 direction = normalize(alpha*u + beta*u - w);
    return Ray(lookFrom, direction);
}