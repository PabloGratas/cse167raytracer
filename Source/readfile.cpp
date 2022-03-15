#include "readfile.h"



// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, float* values) 
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i]; 
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n"; 
      return false;
    }
  }
  return true; 
}

vector<Camera> readmyfile(const char* filename) {
    Scene theScene(0,0);
    vector<Camera> sceneCams;
    vector<glm::vec3> eyes;
    vector<glm::vec3> centers;
    vector<glm::vec3> ups;
    vector<float> fovys;
    int camcount = 0;
    string str, cmd;
    ifstream in;
    vector<vec3> vertVec;
    in.open(filename);
    if (in.is_open()) {
        //transformation stack
        std::stack <glm::mat4> transfstack;
        transfstack.push(glm::mat4(1.0));

        getline (in,str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {

                stringstream s(str);
                s >> cmd;
                int i;
                float values[10];


                bool validinput;


                if (cmd == "size") {
                    validinput = readvals(s, 2, values);
                    
                    if (validinput) {
                        
                        /*ASSIGN to class objects later*/
                        int width = (int)values[0];
                        int height = (int)values[1];
                        theScene.width = width;
                        theScene.height = height;
                    }
                }
                else if (cmd == "camera") {
                  validinput = readvals(s,10,values); // 10 values eye cen up fov
                    if (validinput) {
                      camcount++;
                     /*ASSIGN to class objects later*/
                      glm::vec3 eye = glm::vec3(values[0], values[1], values[2]);
                      glm::vec3 center = glm::vec3(values[3], values[4], values[5]);
                      //not normalized yet
                      glm::vec3 up = glm::vec3(values[6], values[7], values[8]);
         
                      float fovy = (float)values[9];

                      eyes.push_back(eye);
                      centers.push_back(center);
                      ups.push_back(up);
                      fovys.push_back(fovy);
                    }
                }
                else if (cmd == "ambient") {
                  validinput = readvals(s,3,values);
                  if(validinput){
                    theScene.ambient = vec3(values[0], values[1], values[2]);
                  }
                }
                else if (cmd == "directional"){
                  validinput = readvals(s,6,values);
                  if(validinput){
                    theScene.directionala = vec3(values[0], values[1], values[2]);
                    theScene.directionalb = vec3(values[0], values[1], values[2]);
                  }
                }
                else if (cmd == "point"){
                  validinput = readvals(s,3,values);
                  if(validinput){
                    theScene.pointa = vec3(values[0], values[1], values[2]);
                    theScene.pointb = vec3(values[0], values[1], values[2]);
                  }
                }
                else if (cmd == "diffuse"){
                  validinput = readvals(s,3,values);
                  if(validinput){
                    theScene.diffuse = vec3(values[0], values[1], values[2]);
                  }
                }
                else if (cmd == "specular"){
                  validinput = readvals(s,3,values);
                  if(validinput){
                    theScene.specular = vec3(values[0], values[1], values[2]);
                  }
                }
                else if (cmd == "maxverts"){
                  printf("lol"); //I don't think we need the maxverts for anything honestly
                }
                else if (cmd == "vertex"){
                  validinput = readvals(s,3,values);
                  if(validinput){
                    vertVec.push_back(vec3(values[0], values[1], values[2]));
                  }
                }
                else if (cmd == "tri"){
                  validinput = readvals(s,3,values);
                  if(validinput){
                    theScene.triList.push_back(Triangle(vertVec[values[0]], vertVec[values[1]], vertVec[values[2]]));
                    printf("%d\n", theScene.triList.size());
                  }
                }
                else if (cmd == "sphere"){
                  validinput = readvals(s,4,values);
                  if(validinput){
                    theScene.sphereList.push_back(Sphere(vec3(values[0], values[1], values[2]), values[3]));
                  }
                }
                else {
                  continue;
                }
            }
            getline (in,str);
        }

    }
  for(int i = 0; i < camcount; i++){
    sceneCams.push_back(Camera(centers[i], eyes[i], ups[i], fovys[i], &theScene));
  }
  return sceneCams;
}