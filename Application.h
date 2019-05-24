//
// Created by Krzysztof Sychla on 2019-05-24.
//

#ifndef OPENGLSETUP_APPLICATION_H
#define OPENGLSETUP_APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"

class Application {

public:
    Application(GLFWwindow *window);

    ~Application();
    void mainLoop();

private:
    void setRenderBehaviour();

    ShaderProgram simpleColour;

    GLFWwindow* window;
};


#endif //OPENGLSETUP_APPLICATION_H
