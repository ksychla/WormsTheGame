//
// Created by Krzysztof Sychla on 2019-06-23.
//

#include "ThirdPersonCamera.h"

void ThirdPersonCamera::move(GLFWwindow *window, float timePassed, glm::vec3 position, float rotate, glm::mat4 macierz) {
    glm::vec3 constPos = glm::vec3(0,8,30);
//    glm::mat4 rotatet = glm::mat4(1);
    macierz = glm::rotate(macierz, rotate / 50000, up );
//    rotatet = glm::translate(rotatet, position + constPos);
//    rotatet = glm::rotate(rotatet, rotate /50000, up );



    applyRotation(macierz);
    pos = position + constPos;



//    glm::vec3 constPos = glm::vec3(0,8,30);
//    pos = position + constPos;
//
//    glm::mat4 rotation = glm::mat4(1);
//    rotation = glm::rotate(rotation, rotate / 50000, up );
////    rotation = glm::rotate(rotation, 2.f, left );
//    applyRotation(rotation);

}

glm::mat4 ThirdPersonCamera::getView() {
    return glm::lookAt(pos, pos - glm::vec3(0,8,30), up);
}