//
// Created by Krzysztof Sychla on 2019-06-23.
//

#include "ThirdPersonCamera.h"

void ThirdPersonCamera::move(GLFWwindow *window, float timePassed, glm::vec3 position, float rotate) {
    glm::vec3 constPos = glm::vec3(0,4,30);
    pos = position + constPos;

    glm::mat4 rotation = glm::mat4(1);
    rotation = glm::rotate(rotation, rotate / 50000, up );
//    rotation = glm::rotate(rotation, 0.f, left );
    applyRotation(rotation);
}

