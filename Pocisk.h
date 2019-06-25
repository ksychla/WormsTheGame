//
// Created by Krzysztof Sychla on 2019-06-21.
//

#ifndef OPENGLSETUP_POCISK_H
#define OPENGLSETUP_POCISK_H



//#include "MeshFactory.h"
//#include "Mesh.h"
//#include "Parser.h"
#include <glm/glm.hpp>
//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <stdio.h>
#include "generateHeight.h"

class Pocisk {
public:
    Pocisk(generateHeight*);
    ~Pocisk();
    void strzal(glm::vec3 posStart, glm::vec3 velocity);
    glm::vec3 pozycjaPocisku (float czas);
    void enter_press();
    void enter_release();
    int getFlaga() { return flagaPocisku; }
    void setFlaga(int f) { flagaPocisku = f; }
    void setWiatr(glm::vec3 w) { wiatr = w; }
private:
    glm::vec3 wormPos;
    glm::vec2 wormAng;
    float sila;
    float vX;
    float vY;
    float vZ;
    double timePress;
    double timeRelease;
    double timePassedEnter;
    glm::vec3 wiatr;
    int flagaPocisku;
    const float stalyPrzyrostSily = 10;
    const float maxSila = 20.f;
    float grawitacja = 9.81;
    glm::vec3 poprzednia;
    generateHeight* heightMap;
};


#endif //OPENGLSETUP_POCISK_H
