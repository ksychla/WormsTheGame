#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"

    template<typename T>
    size_t vectorsizeof(const typename std::vector<T>& vec)
    {
        return sizeof(T) * vec.size();
    }

    static void glfwError(int id, const char* description)
    {
        std::cout << description << std::endl;
    }

    int main(int argc, char *argv[]) {
        if (!glfwInit()) {
            printf("failed to initialize GLFW.\n");
            return -1;
        }



        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto window = glfwCreateWindow(1000, 600, "awesome", nullptr, nullptr);
        if (!window) {
            return -1;
        }

        glfwMakeContextCurrent(window);
        if (glewInit()) {
            printf("failed to initialize OpenGL\n");
            return -1;
        }

        printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

        Application application(window);
        application.mainLoop();

        return 0;
    }