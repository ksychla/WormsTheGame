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
    void strzal(glm::vec3 posStart, glm::vec2 angStart);
    glm::vec3 pozycjaPocisku (float czas);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    int getFlaga() { return flagaPocisku; }
    void setFlaga(int f) { flagaPocisku = f; }
private:
    glm::vec3 wormPos;
    glm::vec2 wormAng;
    float sila;
    float vX;
    float vY;
    float vZ;
    int flagaPocisku;
    const float stalyPrzyrostSily = 1;
    const float maxSila = 10;
    float grawitacja = 9.81;
    glm::vec3 poprzednia;
    generateHeight* heightMap;
};


#endif //OPENGLSETUP_POCISK_H
