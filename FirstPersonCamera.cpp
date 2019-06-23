//
// Created by Krzysztof Sychla on 2019-06-23.
//

#include "FirstPersonCamera.h"


void FirstPersonCamera::move(GLFWwindow *window, float timePassed, glm::vec3 position, float rotate) {
    glm::vec3 dir = glm::vec3(0);
    float rotate_up = 0;
    float rotate_left = 0;
    float rotationSpeed = 2.f;

    pos = position;
    pos += glm::vec3(0,10,-1.5);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) rotate_up += -rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotate_left += rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rotate_up += rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotate_left += -rotationSpeed ;

    glm::mat4 rotation = glm::mat4(1);
    rotation = glm::rotate(rotation, rotate_left * timePassed, up );
    rotation = glm::rotate(rotation, rotate_up * timePassed, left );
    applyRotation(rotation);
}
