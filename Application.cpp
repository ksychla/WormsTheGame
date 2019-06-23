//
// Created by Krzysztof Sychla on 2019-05-24.
//

#include "Application.h"

#include "Mesh.h"
#include "MeshFactory.h"
#include "Terrain.h"
#include "Texture.h"
#include "Water.h"
#include "Parser.h"


#include "ShaderProgram.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        myApplication->currentCamera = &myApplication->camera;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS){
//        myApplication->currentCamera = &myApplication->onKeyRotationCamera;
    }
}

void window_focus_callback(GLFWwindow* window, int focused)
{
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);

    if (focused)
    {
        // The window gained input focus
    }
    else
    {
        // The window lost input focus
    }
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        printf("halo");
    }
}

Application::Application(GLFWwindow *window) : window(window) {
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetWindowUserPointer(window, this);

    currentCamera = &thirdPersonCamera;
}

Application::~Application() {
}

void Application::changeCamera(GLFWwindow *window, Snowman* snowman){
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        if (whichCamera){
            myApplication->currentCamera = &myApplication->firstPersonCamera;
        }else{
            myApplication->currentCamera = &myApplication->thirdPersonCamera;  // 3'rd person camera
        }
        whichCamera = !whichCamera;
        time = 100;
        snowman->changeCamera(myApplication->currentCamera);
    }
}

void Application::mainLoop() {

    Terrain terrain(1,1,5);
    Mesh t = terrain.drawTerrain();

    Water water(500);
    Mesh w = water.createWater();

    Texture texture("Textures/Grass.jpg");
    GLuint tex = texture.readTexture();

//    Wczytywanie bałwana

    Parser* parser = new Parser();

    Mesh missel = parser->getOBJ("../Models/snowman.obj");





    simpleColor.loadProgram("../Shaders/SimpleColour/",
                             "vertex.glsl", nullptr, "fragment.glsl");

    simpleColor.use();



    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspect = (float) width / (float) height;

    glm::mat4 M = glm::mat4(1.f);
    glm::mat4 P = glm::perspective(glm::radians(45.f), aspect, 0.1f, 100.0f );
    glm::mat4 MVP = glm::mat4(1.f);

    setRenderBehaviour();
//    Camera* cam = new Camera();
    Snowman* snowman = new Snowman(glm::vec3(0,0,0), currentCamera);

    double time1 = glfwGetTime();
    double time2;
    double timePassed;


    while(!glfwWindowShouldClose(window)) {
        time2 = glfwGetTime();
        timePassed = time2 - time1;

        if(time == 0) {
            changeCamera(window, snowman);
        }else{
            time--;
        }


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        M = glm::mat4(1.f);
        M = glm::scale(M, glm::vec3(1));
        M = glm::translate(M, glm::vec3(0.f,0.f,0.f) );
        MVP = P * currentCamera->getView() * M;
        glUniformMatrix4fv(simpleColor.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(simpleColor.getU("M"), 1, GL_FALSE, glm::value_ptr(M));
        glUniformMatrix4fv(simpleColor.getU("V"), 1, GL_FALSE, glm::value_ptr(currentCamera->getView()));
        glUniformMatrix4fv(simpleColor.getU("P"), 1, GL_FALSE, glm::value_ptr(P));
        glUniform4f(simpleColor.getU("lp"),0,-10,-100,1);

//        glUniform1i(simpleColor.getU("textureMap"),0);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,tex);

//        glEnableVertexAttribArray(simpleColor.getU("texCoord"));  //Włącz przesyłanie danych do atrybutu texCoord0
//        glVertexAttribPointer(simpleColor.getU("texCoord"),2,GL_FLOAT,false,0,texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0


        t.bind();
        glDrawElements(GL_TRIANGLES, t.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);

        w.bind();
        glDrawElements(GL_TRIANGLES, w.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);


        snowman->move(window, timePassed);

        float tempRot = snowman->getRotation();
        glm::vec3 tempPos = snowman->getPos();

        M = glm::mat4(1.f);
        M = glm::scale(M, glm::vec3(1));
        M = glm::translate(M, tempPos);
        M = glm::rotate(M, (float)(tempRot / 100000), glm::vec3(0,1,0) );
//        M = glm::translate(M, glm::vec3(0,0,0));
//        M = glm::translate(M, tempPos);



//        glm::vec3 posTemp = snowman->getPos();



//        M = glm::translate(M, posTemp);
        MVP = P * currentCamera->getView() * M;
        glUniformMatrix4fv(simpleColor.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(simpleColor.getU("M"), 1, GL_FALSE, glm::value_ptr(M));
        glUniformMatrix4fv(simpleColor.getU("V"), 1, GL_FALSE, glm::value_ptr(currentCamera->getView()));
        glUniformMatrix4fv(simpleColor.getU("P"), 1, GL_FALSE, glm::value_ptr(P));
        glUniform4f(simpleColor.getU("lp"),0,-10,-100,1);

        missel.bind();
        glDrawElements(GL_TRIANGLES, missel.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);


        glfwSwapBuffers(window);
        glfwPollEvents();

        time1 = time2;
    };

    simpleColor.freeProgram();
}

void Application::setRenderBehaviour() {
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.22f,
                 0.69f,
                 0.87f,
                 1.f
    );
}
