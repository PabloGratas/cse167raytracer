class Intersection { //See page 27 of the ray tracing slides
    
    glm::vec3 pos;
    glm::vec3 surNorm;
    glm::vec3 incoming;
    hittable obj; //Hittable is what they call our rendered objects in the weekend guide, we can change this later.
    float dist;

    public:
        Intersection (glm::vec3 pos, glm::vec3 surNorm, glm::vec3 incoming, hittable obj, float dist);
        ~Intersection();


};
