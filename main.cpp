#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include "ShaderProgram.h"
#include "MeshFactory.h"
#include "Mesh.h"

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



        ShaderProgram simpleColour;
        simpleColour.loadProgram("../Shaders/SimpleColour/",
                                 "vertex.glsl", nullptr, "fragment.glsl");

        simpleColour.use();

        glm::vec3 cameraPos = glm::vec3(0,0,0);
        glm::vec3 cameraFront = glm::vec3(0,0,-1);
        glm::vec3 cameraUp = glm::vec3(0,1,0);

        glm::mat4 M = glm::mat4(1.f);
        glm::mat4 V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 P = glm::perspective(45.f, 1.0f, 0.1f, 100.0f );
        glm::mat4 MVP = M * V * P;

        while(!glfwWindowShouldClose(window)) {
            glClearColor(0.f,
                         0.f,
                         1.f,
                         1.f
                         );
            glClear(GL_COLOR_BUFFER_BIT);

            V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

            M = glm::mat4(1.f);
            glm::scale(M, glm::vec3(0.25));
            glm::translate(M, glm::vec3(0.f,0.f, -2000.f) );
            MVP = M * V * P;
            glUniformMatrix4fv(simpleColour.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

            triangle.bind();

            glDrawElements(GL_TRIANGLES, triangle.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);

            M = glm::mat4(1.f);
            V = glm::mat4(1.f);
            P = glm::mat4(1.f);
            glm::scale(M, glm::vec3(0.25));
            glm::translate(M, glm::vec3(0.f,0.f, -4.f) );
            MVP = M * V * P;
            glUniformMatrix4fv(simpleColour.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

            cube.bind();

            //glDrawElements(GL_TRIANGLES, cube.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window);
            glfwPollEvents();
        };

        simpleColour.freeProgram();

        return 0;
    }