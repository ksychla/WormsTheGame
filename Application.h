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
#include <vector>
#include <unistd.h>
//#include <ctime>
#include <cstdlib>
#include <cstdio>


#include "ShaderProgram.h"
#include "Camera.h"
#include "OnKeyRotationCamera.h"
#include "FirstPersonCamera.h"
#include "ThirdPersonCamera.h"
#include "Snowman.h"
#include "Mesh.h"

class Application {
    friend void key_callback(GLFWwindow*, int, int, int, int);
    friend void window_focus_callback(GLFWwindow*, int);
    friend void window_size_callback(GLFWwindow*, int, int);
    friend void cursor_position_callback(GLFWwindow*, double, double);
    friend void mouse_button_callback(GLFWwindow*, int, int, int);
public:
    Application(GLFWwindow *window);

    ~Application();
    void mainLoop();

private:
    void setRenderBehaviour();
    void changeCamera(GLFWwindow *window, Snowman*);
    glm::vec3 losujWiatr();

    int timeCamera;
    bool whichCamera = true;
    Camera camera;
    ThirdPersonCamera thirdPersonCamera;
    FirstPersonCamera firstPersonCamera;
    Camera* currentCamera;
    Snowman* currentSnowman;

    GLuint readTexture(const char* filename);

    ShaderProgram terrainShader;
    ShaderProgram snowmanShader;
    ShaderProgram missailShader;
    ShaderProgram waterShader;
    ShaderProgram guiShader;

    int healthRed;
    int healthBlue;
    glm::vec3 wiatr;
    bool turn;


    GLFWwindow* window;

    void
    drawSnowman1(GLuint tex, Mesh &snowmanMesh, const glm::mat4 &P, glm::mat4 &MVP, Snowman *snowman,
                     Mesh &bazooka, int health);
};


#endif //OPENGLSETUP_APPLICATION_H
