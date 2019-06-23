//
// Created by Krzysztof Sychla on 2019-06-23.
//

#ifndef OPENGLSETUP_FIRSTPERSONCAMERA_H
#define OPENGLSETUP_FIRSTPERSONCAMERA_H

#include "Camera.h"


class FirstPersonCamera : public Camera {
public:
    void move(GLFWwindow* window, float timePassed, glm::vec3 position, float rotate);
//    void moveWithPlayer(glm::vec3 position, float rotate);
};


#endif //OPENGLSETUP_FIRSTPERSONCAMERA_H
