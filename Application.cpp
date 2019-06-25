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
#include "Game.h"
#include "generateHeight.h"
#include "Pocisk.h"
#include "lodepng.h"


#include "ShaderProgram.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_E && action == GLFW_PRESS){
//        myApplication->currentCamera = &myApplication->camera;
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

    healthRed = 100;
    healthBlue = 100;
    wiatr = glm::vec3(0.f);
    turn = 0;

    currentCamera = &thirdPersonCamera;
}

Application::~Application() { }

void Application::changeCamera(GLFWwindow *window, Snowman* snowman){
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        if (whichCamera){
            myApplication->currentCamera = &myApplication->firstPersonCamera;
        }else{
            myApplication->currentCamera = &myApplication->thirdPersonCamera;  // 3'rd person camera
        }
        whichCamera = !whichCamera;
        timeCamera = 100;
        snowman->changeCamera(myApplication->currentCamera);
    }
}

glm::vec3 Application::losujWiatr() {
    glm::vec3 tmp;
    int maxWiatr = 30;
    tmp.x = rand()%(2*maxWiatr)-maxWiatr;
    tmp.y = rand()%(2*maxWiatr)-maxWiatr;
    tmp.z = rand()%(2*maxWiatr)-maxWiatr;
    return tmp;
}

GLuint Application::readTexture(const char* filename) {
    GLuint texture;
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamięci karty graficznej
    glGenTextures(1,&texture); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, texture); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

void Application::mainLoop() {

    Terrain terrain(1,1,5);
    Mesh t = terrain.drawTerrain();

    generateHeight* heightMap = terrain.getHeight();

    Water water(500);
    Mesh w = water.createWater();

//    Texture texture("../Textures/tiger.png");
//    GLuint tex = texture.readTexture();
//
//    Texture texture2("../Textures/tiger.png");
//    GLuint tex2 = texture2.readTexture();

    GLuint tex = readTexture("../Textures/tiger.png");

//    Wczytywanie bałwana

    Parser* parser = new Parser();

    Mesh snowmanMesh = parser->getOBJ("../Models/snowman.obj", glm::vec3(1,1,1));

    Parser* par = new Parser();

    Mesh bazooka = par->getOBJ("../Models/bazookaMissail.obj", glm::vec3(0,0,0));

    Parser* pociskObiekt = new Parser();
    Mesh pociskMesh = pociskObiekt->getOBJ("../Models/Missel.obj",glm::vec3(0,0,1));

    Parser* spherePars = new Parser();
    Mesh sphere = spherePars->getOBJ("../Models/sphere.obj",glm::vec3(1,1,0));





    terrainShader.loadProgram("../Shaders/SimpleColour/",
                             "vertex.glsl", nullptr, "fragment.glsl");

    snowmanShader.loadProgram("../Shaders/SimpleColour/",
            "vertexSnowman.glsl", nullptr, "fragmentSnowman.glsl");

    guiShader.loadProgram("../Shaders/SimpleColour/",
            "vertexGui.glsl", nullptr, "fragmentGui.glsl");



    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspect = (float) width / (float) height;

    glm::mat4 M = glm::mat4(1.f);
    glm::mat4 P = glm::perspective(glm::radians(60.f), aspect, 0.1f, 100.0f );
    glm::mat4 MVP = glm::mat4(1.f);

    setRenderBehaviour();
    Snowman* snowman = new Snowman(heightMap, currentCamera, glm::vec2(10,20));
    Snowman* snowman2 = new Snowman(heightMap, nullptr, glm::vec2(70,60));
    currentSnowman = snowman;

    double time1 = glfwGetTime();
    double time2;
    double timePassed;

    double currentTime, fpsNow = glfwGetTime();
    int nbFrames = 0;

    Pocisk pocisk(heightMap);


    while(!glfwWindowShouldClose(window)) {
        nbFrames++;
        currentTime = glfwGetTime();
        if ( currentTime - fpsNow >= 1.0 ){
            printf("%d FPS\n", nbFrames);
            if (pocisk.getFlaga() != 1) wiatr = losujWiatr();
            pocisk.setWiatr(wiatr);
            nbFrames = 0;
            fpsNow += 1.0;
            printf("Wiatr w kierunku\n x:%f\ty:%f\t%f\n", wiatr.x, wiatr.y, wiatr.z );
            printf("Zdrowie niebieskiego: %d\n", healthBlue);
            printf("Zdrowie czerwonego: %d\n", healthRed);
        }
        time2 = glfwGetTime();
        timePassed = time2 - time1;

        if(timeCamera == 0) {
            changeCamera(window, snowman);
        }else{
            timeCamera--;
        }

        terrainShader.use();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        M = glm::mat4(1.f);
        M = glm::scale(M, glm::vec3(1));
        M = glm::translate(M, glm::vec3(0.f,-20.f,0.f) );
        MVP = P * currentSnowman->getView() * M;
        glUniformMatrix4fv(terrainShader.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(terrainShader.getU("M"), 1, GL_FALSE, glm::value_ptr(M));
        glUniformMatrix4fv(terrainShader.getU("V"), 1, GL_FALSE, glm::value_ptr(currentCamera->getView()));
        glUniformMatrix4fv(terrainShader.getU("P"), 1, GL_FALSE, glm::value_ptr(P));
        glUniform4f(terrainShader.getU("lp"),0,50,-100,1);
        glUniform4f(terrainShader.getU("lp2"),0,50,100,1);



//        glEnableVertexAttribArray(terrainShader.getU("texCoord"));  //Włącz przesyłanie danych do atrybutu texCoord0
//        glVertexAttribPointer(terrainShader.getU("texCoord"),2,GL_FLOAT,false,0,texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0


        t.bind();
        glDrawElements(GL_TRIANGLES, t.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);

        w.bind();
        glDrawElements(GL_TRIANGLES, w.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);


        currentSnowman->move(window, timePassed, pocisk, whichCamera);

        float tempRot = currentSnowman->getRotation();
        glm::vec3 tempPos = currentSnowman->getPos();

        M = glm::mat4(1.f);
        M = glm::scale(M, glm::vec3(1));
        M = glm::translate(M, tempPos);
        M = glm::rotate(M, (float)(tempRot / 100000), glm::vec3(0,1,0) );
//        M = glm::translate(M, glm::vec3(0,0,0));
//        M = glm::translate(M, tempPos);

        drawSnowman1(tex, snowmanMesh, P, MVP, snowman, bazooka, healthBlue);
        drawSnowman1(tex, snowmanMesh, P, MVP, snowman2, bazooka, healthRed);


        //printf("%d\n", pocisk.getFlaga());
        glm::vec3 tmpPozPocisku;
        if(pocisk.getFlaga() == 2){

//            pocisk.pozycjaPocisku();
            glm::mat4 M2 = glm::mat4(1.f);
            M2 = glm::translate(M2, pocisk.pozycjaPocisku(timePassed));
            M2 = glm::rotate(M2, -(float)3.141592/2, glm::vec3(1,0,0));
            MVP = P * currentSnowman->getView() * M2;
            glUniformMatrix4fv(snowmanShader.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
            glUniformMatrix4fv(snowmanShader.getU("M"), 1, GL_FALSE, glm::value_ptr(M2));
            glUniformMatrix4fv(snowmanShader.getU("V"), 1, GL_FALSE, glm::value_ptr(currentCamera->getView()));
            glUniformMatrix4fv(snowmanShader.getU("P"), 1, GL_FALSE, glm::value_ptr(P));
            glUniform4f(snowmanShader.getU("lp"),0,50,-100,1);
            glUniform4f(snowmanShader.getU("lp2"),0,50,100,1);



            pociskMesh.bind();
            glDrawElements(GL_TRIANGLES, pociskMesh.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);
//            printf("halo");
            tmpPozPocisku = pocisk.pozycjaPocisku(timePassed);
        }
        else if(pocisk.getFlaga() >= 3)
        {
            glm::mat4 M3 = glm::mat4(1.f);
            M3 = glm::translate(M3, tmpPozPocisku);
            M3 = glm::scale(M3, glm::vec3(pocisk.getFlaga()*0.1));
//            M3 = glm::translate(M3, glm::vec3(0.f,-pocisk.getFlaga()*0.1,0.f));



            MVP = P * currentSnowman->getView() * M3;
            glUniformMatrix4fv(snowmanShader.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
            glUniformMatrix4fv(snowmanShader.getU("M"), 1, GL_FALSE, glm::value_ptr(M3));
            glUniformMatrix4fv(snowmanShader.getU("V"), 1, GL_FALSE, glm::value_ptr(currentCamera->getView()));
            glUniformMatrix4fv(snowmanShader.getU("P"), 1, GL_FALSE, glm::value_ptr(P));
            glUniform4f(snowmanShader.getU("lp"),0,50,-100,1);
            glUniform4f(snowmanShader.getU("lp2"),0,50,100,1);

            sphere.bind();
            glDrawElements(GL_TRIANGLES, sphere.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);

            pocisk.setFlaga(pocisk.getFlaga()+1);
            if (pocisk.getFlaga()==150){
                pocisk.setFlaga(0);

                float snowX = snowman->getPos().x, snowY = snowman->getPos().y, snowZ = snowman->getPos().z;
                float snow2X = snowman2->getPos().x, snow2Y = snowman2->getPos().y, snow2Z = snowman2->getPos().z;
                float dmgX = tmpPozPocisku.x, dmgY = tmpPozPocisku.y, dmgZ = tmpPozPocisku.z;
                float range = 15/2;
                float snowR = (snowX - dmgX) * (snowX - dmgX) + (snowZ - dmgZ) * (snowZ - dmgZ);
                if( snowR < range * range ) {
                    healthBlue -= (int)((1 - snowR / (range * range)) * 100);
                }
                float snowR2 = (snow2X - dmgX) * (snow2X - dmgX) + (snow2Z - dmgZ) * (snow2Z - dmgZ);
                if( snowR2 < range * range ) {
                    healthRed -= (int)((1 - snowR2 / (range * range)) * 100);
                }
                turn = !turn;
                if(turn) {
                    currentSnowman = snowman2;
                }else{
                    currentSnowman = snowman;
                }
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        time1 = time2;
    };

    terrainShader.freeProgram();
    snowmanShader.freeProgram();
    guiShader.freeProgram();
}

void Application::drawSnowman1(GLuint tex, Mesh &snowmanMesh, const glm::mat4 &P, glm::mat4 &MVP, Snowman *snowman,
                               Mesh &bazooka, int health)
{
    if(health > 0){
        snowmanShader.use();
        MVP = P * currentSnowman->getView() * snowman->getModel();
        glm::mat4 M = snowman->getModel();
        glUniformMatrix4fv(snowmanShader.getU("MVP"), 1, GL_FALSE, value_ptr(MVP));
        glUniformMatrix4fv(snowmanShader.getU("M"), 1, GL_FALSE, value_ptr(M));
        glUniformMatrix4fv(snowmanShader.getU("V"), 1, GL_FALSE, value_ptr(currentCamera->getView()));
        glUniformMatrix4fv(snowmanShader.getU("P"), 1, GL_FALSE, value_ptr(P));
        glUniform4f(snowmanShader.getU("lp"), 0, 50, -100, 1);
        glUniform4f(snowmanShader.getU("lp2"), 0, 50, 100, 1);

//        glUniform1i(snowmanShader.getU("textureMap"), 0);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D,tex);

        snowmanMesh.bind();
        glDrawElements(GL_TRIANGLES, snowmanMesh.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);

        M = glm::mat4(1);
        M = glm::translate(M, glm::vec3(2,6,0));
        M = glm::rotate(M, 1.7f, glm::vec3(0,1,0) );
        M = snowman->getModel() * M;
        MVP = P * currentSnowman->getView() * M;
        glUniformMatrix4fv(snowmanShader.getU("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(snowmanShader.getU("M"), 1, GL_FALSE, glm::value_ptr(M));
        glUniformMatrix4fv(snowmanShader.getU("V"), 1, GL_FALSE, glm::value_ptr(currentCamera->getView()));
        glUniformMatrix4fv(snowmanShader.getU("P"), 1, GL_FALSE, glm::value_ptr(P));
        glUniform4f(snowmanShader.getU("lp"),0,50,-100,1);
        glUniform4f(snowmanShader.getU("lp2"),0,50,100,1);

        bazooka.bind();
        glDrawElements(GL_TRIANGLES, bazooka.getIndiciesCount(), GL_UNSIGNED_INT, nullptr);
    }
}

void Application::setRenderBehaviour() {
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.22f,
                 0.69f,
                 0.87f,
                 1.f
    );
}

//TODO kat wystrzalu //z pierwszej kamery do pocisku 👌(KINDA)
//TODO drógie źródło światła 👌
//TODO dopisanie akcji nacisku myszki w strzelaniu 👌
//TODO (NIE) pasek sily
//TODO tracenie zdrowia robaka 👌
//TODO rysuj balwana jesli healtsdfjshdk > 0 👌
//TODO naprawić kamere
//TODO tekstura
//TODO przelaczanie kamery 👌
