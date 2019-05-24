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

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dir += front ;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) dir += left ;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dir += -front ;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) dir += -left ;

    pos+= dir * timePassed;
}

void Camera::applyRotation(glm::mat4 rotation) {
    pos   = toVec3(rotation * glm::vec4(pos  ,1));
    front = toVec3(rotation * glm::vec4(front,1));
    up    = toVec3(rotation * glm::vec4(up   ,1));
    left  = toVec3(rotation * glm::vec4(left ,1));
}

