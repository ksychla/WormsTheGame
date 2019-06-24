//
// Created by Krzysztof Sychla on 2019-05-24.
//

#include "OnKeyRotationCamera.h"

#include <glm/gtc/matrix_transform.hpp>

void OnKeyRotationCamera::move(GLFWwindow *window, float timePassed, glm::vec3 position, float rotate, glm::mat4 g) {
    Camera::move(window, timePassed, position, rotate, g);

    float rotate_left = 0;
    float rotate_up = 0;

    float rotationSpeed = 10.f;

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) rotate_up += rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotate_left += rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rotate_up -= rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotate_left -= rotationSpeed ;
//    if(glfwGetKey(window, GLFW_))



//    glm::mat4 rotate = glm::mat4(1);
//              rotate = glm::rotate(rotate, rotate_left * timePassed, up );
//              rotate = glm::rotate(rotate, rotate_up * timePassed, left );

//    applyRotation(rotate);
}
