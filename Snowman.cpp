//
// Created by Krzysztof Sychla on 2019-06-22.
//

#include "Snowman.h"

inline static glm::vec3 toVec3(glm::vec4 a){
    return glm::vec3(a.x, a.y, a.z);
}

Snowman::Snowman(glm::vec3 position, Camera* cam) {
    pos = position;
    camera = cam;
}

void Snowman::move(GLFWwindow* window, double timePassed, bool flaga){
    glm::vec3 dir = glm::vec3(0);
    float rotate_up = 0;
    float rotate_left = 0;
    float rotationSpeed = 100.f;

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) dir += front*5.f ;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotate_left += rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) dir += -front*5.f ;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotate_left += -rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) rotate_up -= rotationSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) rotate_up += rotationSpeed;


    if(flaga){
        rotation += rotate_left;
        glm::mat4 rotate = glm::mat4(1);
        rotate = glm::rotate(rotate, rotate_left / 50000, up );
//    rotate = glm::rotate(rotate, rotate_up * timePassed, left );
        applyRotation(rotate);
        pos+= dir * (float)timePassed;
    }


    camera->move(window, timePassed, pos, rotate_left);
}

void Snowman::applyRotation(glm::mat4 rotation) {
//    pos   = toVec3(rotation * glm::vec4(pos  ,1));
    front = toVec3(rotation * glm::vec4(front,1));
//    up    = toVec3(rotation * glm::vec4(up   ,1));
//    left  = toVec3(rotation * glm::vec4(left ,1));
}