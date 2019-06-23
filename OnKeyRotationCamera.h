//
// Created by Krzysztof Sychla on 2019-05-24.
//

#ifndef OPENGLSETUP_ONKEYROTATIONCAMERA_H
#define OPENGLSETUP_ONKEYROTATIONCAMERA_H

#include "Camera.h"

class OnKeyRotationCamera : public Camera{
public:
    void move(GLFWwindow *window, float timePassed, glm::vec3 position, float rotate) override;
};


#endif //OPENGLSETUP_ONKEYROTATIONCAMERA_H
