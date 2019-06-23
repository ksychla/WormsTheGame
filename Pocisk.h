//
// Created by Krzysztof Sychla on 2019-06-21.
//

#ifndef OPENGLSETUP_POCISK_H
#define OPENGLSETUP_POCISK_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

class Pocisk {
public:
    Pocisk();
    ~Pocisk();
    void strzal(glm::vec3 posStart);
    glm::vec4 pozycjaPocisku (glm::vec4 poprzednia, float czas);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
private:
    glm::vec3 wormPos;
    glm::vec2 wormAng;
    float sila;
    float vX;
    float vY;
    float vZ;
    int flagaPocisku;
    const float stalyPrzyrostSily;
    const float maxSila;
    float grawitacja = 9.81;
};


#endif //OPENGLSETUP_POCISK_H
