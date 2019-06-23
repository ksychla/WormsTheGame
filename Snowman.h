//
// Created by Krzysztof Sychla on 2019-06-22.
//

#ifndef OPENGLSETUP_SNOWMAN_H
#define OPENGLSETUP_SNOWMAN_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Camera.h"

class Snowman {
public:
    Snowman(glm::vec3 position, Camera* cam);
    ~Snowman();
    void move(GLFWwindow* window, float timePassed);
    glm::vec3 getPos() { return pos; }
    float getRotation() { return rotation; }
private:
    int health = 100;

    Camera* camera;

    glm::vec3 pos = glm::vec3(0,0,2);
    glm::vec3 front = glm::vec3(0,0,-1);
    glm::vec3 up = glm::vec3(0,1,0);
    glm::vec3 left = glm::vec3(-1,0,0);
    float rotation = 0;

    void applyRotation(glm::mat4 rotation);
};


#endif //OPENGLSETUP_SNOWMAN_H
