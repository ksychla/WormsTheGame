//
// Created by Krzysztof Sychla on 2019-05-24.
//

#include "Camera.h"
inline static glm::vec3 toVec3(glm::vec4 a){
    return glm::vec3(a.x, a.y, a.z);
}

glm::mat4 Camera::getView() {
    return glm::lookAt(pos, pos + front, up);
}

void Camera::move(GLFWwindow *window, float timePassed) {
    glm::vec3 dir = glm::vec3(0);
    float rotate_up = 0;
    float rotate_left = 0;
    float rotationSpeed = 2.f;


    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) dir += front*5.f ;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotate_left += rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) dir += -front*5.f ;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotate_left += -rotationSpeed ;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) rotate_up -= rotationSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) rotate_up += rotationSpeed;

    pos+= dir * timePassed;
    glm::mat4 rotate = glm::mat4(1);
    rotate = glm::rotate(rotate, rotate_left * timePassed, up );
    rotate = glm::rotate(rotate, rotate_up * timePassed, left );
    applyRotation(rotate);
}

void Camera::applyRotation(glm::mat4 rotation) {
    pos   = toVec3(rotation * glm::vec4(pos  ,1));
    front = toVec3(rotation * glm::vec4(front,1));
    up    = toVec3(rotation * glm::vec4(up   ,1));
    left  = toVec3(rotation * glm::vec4(left ,1));
}

