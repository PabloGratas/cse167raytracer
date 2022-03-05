#include "Intersection.h"

Intersection::Intersection(glm::vec3 pos, glm::vec3 surNorm, glm::vec3 incoming, hittable obj, float dist) :
    pos(pos),
    surNorm(surNorm),
    incoming(incoming),
    obj(obj),
    dist(dist)
{}