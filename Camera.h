//
// Created by Krzysztof Sychla on 2019-05-24.
//

#ifndef OPENGLSETUP_CAMERA_H
#define OPENGLSETUP_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    virtual void move(GLFWwindow* window, float timePassed);
    glm::mat4 getView();
protected:
    void applyRotation(glm::mat4 rotation);

    glm::vec3 pos = glm::vec3(0,0,2);
    glm::vec3 front = glm::vec3(0,0,-1);
    glm::vec3 up = glm::vec3(0,1,0);
    glm::vec3 left = glm::vec3(-1,0,0);
};



#endif //OPENGLSETUP_FREECAMERA_H
