//
// Created by Krzysztof Sychla on 2019-06-22.
//

#ifndef OPENGLSETUP_SNOWMAN_H
#define OPENGLSETUP_SNOWMAN_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Pocisk.h"
#include "generateHeight.h"

class Snowman {
public:
    Snowman(generateHeight*, Camera* cam, glm::vec2);
    ~Snowman();
    void move(GLFWwindow* window, double timePassed, bool, Pocisk&);
    glm::vec3 getPos() { return pos; }
    float getRotation() { return rotation; }
    void changeCamera(Camera* cam) { camera = cam; }
private:
    int health = 100;

    generateHeight* height;

    Camera* camera;

//    Pocisk* pocisk;
    bool flagaEnter = false;
    glm::vec3 pos;
    glm::vec3 front = glm::vec3(0,0,-1);
    glm::vec3 up = glm::vec3(0,1,0);
    glm::vec3 left = glm::vec3(-1,0,0);
    float rotation = 0;

    void applyRotation(glm::mat4 rotation);
};


#endif //OPENGLSETUP_SNOWMAN_H
