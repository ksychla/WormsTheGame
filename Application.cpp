//
// Created by Krzysztof Sychla on 2019-05-24.
//

#include "Application.h"

#include "Mesh.h"
#include "MeshFactory.h"

#include "ShaderProgram.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
        myApplication->currentCamera = &myApplication->camera;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS){
        myApplication->currentCamera = &myApplication->onKeyRotationCamera;
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

    }
}

Application::Application(GLFWwindow *window) : window(window) {
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetWindowUserPointer(window, this);

    currentCamera = &camera;
}

Application::~Application() {
}

void Application::mainLoop() {
    Mesh triangle = MeshFactory()
            .addPos( glm::vec3(-1.0f, -1.0f, 0.0f) )
            .addPos( glm::vec3( 1.0f, -1.0f, 0.0f) )
            .addPos( glm::vec3( 0.0f,  1.0f, 0.0f) )
            .addCol( glm::vec3( 0, 0, 0) )
            .addCol( glm::vec3( 1, 0, 1) )
            .addCol( glm::vec3( 1, 1, 1) )
            .addInd( 0, 1, 2 )
            .create();

    Mesh cube = MeshFactory()
            .addPos( glm::vec3(-1, -1, -1) )
            .addPos( glm::vec3( 1, -1, -1) )
            .addPos( glm::vec3( 1,  1, -1) )
            .addPos( glm::vec3(-1,  1, -1) )
            .addPos( glm::vec3(-1, -1,  1) )
            .addPos( glm::vec3( 1, -1,  1) )
            .addPos( glm::vec3( 1,  1,  1) )
            .addPos( glm::vec3(-1,  1,  1) )

            .addCol( glm::vec3(0,0,0) )
            .addCol( glm::vec3(0,0,1) )
            .addCol( glm::vec3(0,1,0) )
            .addCol( glm::vec3(0,1,1) )
            .addCol( glm::vec3(1,0,0) )
            .addCol( glm::vec3(1,0,1) )
            .addCol( glm::vec3(1,1,0) )
            .addCol( glm::vec3(1,1,1) )

            .addInd(0, 1, 3)
            .addInd(3, 1, 2)
            .addInd(1, 5, 2)
            .addInd(2, 5, 6)
            .addInd(5, 4, 6)
            .addInd(6, 4, 7)
            .addInd(4, 0, 7)
            .addInd(7, 0, 3)
            .addInd(3, 2, 7)
            .addInd(7, 2, 6)
            .addInd(4, 5, 0)
            .addInd(0, 5, 1)

            .create();



    simpleColour.loadProgram("../Shaders/SimpleColour/",
                             "vertex.glsl", nullptr, "fragment.glsl");

    simpleColour.use();



    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspect = (float) width / (float) height;

    glm::mat4 M = glm::mat4(1.f);
    glm::mat4 P = glm::perspective(glm::radians(45.f), aspect, 0.1f, 100.0f );
    glm::mat4 MVP = glm::mat4(1.f);

    setRenderBehaviour();

    double time1 = glfwGetTime();
    double time2;
    double timePassed;
    while(!glfwWindowShouldClose(window)) {
        time2 = glfwGetTime();
        timePassed = time2 - time1;
        currentCamera->move(window, timePassed);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        M = glm::mat4(1.f);
        M = glm::scale(M, glm::vec3(0.5));
        M = glm::translate(M, glm::vec3(2.f,0.f,-1.f) );
        MVP = P * currentCamera->getView() * M;
        glUniformMatrix4fv(simpleColour.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

        triangle.bind();

        glDrawElements(GL_TRIANGLES, triangle.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);

        M = glm::mat4(1.f);
        M = glm::translate(M, glm::vec3(0.f,0.f, -4.f) );
        M = glm::rotate(M, 30.f, glm::vec3(1.f,1.f,0.f) );
        MVP = P * currentCamera->getView() * M;
        glUniformMatrix4fv(simpleColour.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

        cube.bind();

        glDrawElements(GL_TRIANGLES, cube.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();

        time1 = time2;
    };

    simpleColour.freeProgram();
}

void Application::setRenderBehaviour() {
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.f,
                 0.f,
                 1.f,
                 1.f
    );
}
