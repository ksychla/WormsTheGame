//
// Created by Krzysztof Sychla on 2019-06-21.
//

#ifndef OPENGLSETUP_POCISK_H
#define OPENGLSETUP_POCISK_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <cmath>

class Pocisk {
public:
    Pocisk();
    ~Pocisk();
    void strzal();
    glm::vec4 pozycjaPocisku (glm::vec4 poprzednia, double czas);

private:
    glm::vec3 wormPos;
    glm::vec2 wormAng;
    float sila;
    float vX;
    float vY;
    float vZ;
    int flagaPocisku;
};


#endif //OPENGLSETUP_POCISK_H
