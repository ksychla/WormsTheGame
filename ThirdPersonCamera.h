//
// Created by Krzysztof Sychla on 2019-06-23.
//

#ifndef OPENGLSETUP_THIRDPERSONCAMERA_H
#define OPENGLSETUP_THIRDPERSONCAMERA_H

#include "Camera.h"

class ThirdPersonCamera : public Camera{
    void move(GLFWwindow* window, float timePassed, glm::vec3 position, float rotate);
};


#endif //OPENGLSETUP_THIRDPERSONCAMERA_H
