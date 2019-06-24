//
// Created by Krzysztof Sychla on 2019-06-21.
//

#include "Pocisk.h"

Pocisk::Pocisk(generateHeight* height){
    flagaPocisku = 0;
    heightMap = height;
}

Pocisk::~Pocisk(){

}

void Pocisk::strzal(glm::vec3 posStart, glm::vec2 angStart) {
    poprzednia = posStart;
    poprzednia.y += 11.f;

//    Parser* parser = new Parser();
//
//    Mesh missel = parser->getOBJ("../Models/Missel.obj");



    wormPos = posStart; //tu przypisać pozycje robaka, x, y, z //pierwsza pozycja pocisku
    wormPos.y += 11.f;
    //wormAng = glm::vec2(-3.14/2, 0.0f); //kąt względem x?, kąt góra-dół (oś z)
    wormAng = angStart;
    wormAng.y = 0.5f;
    //printf("%f %f %f\n", poprzednia.x, poprzednia.y, poprzednia.z);

    sila=20.f; //sile tez by mozna bylo przekazać, robić ją jak dlugo trzyma sie myszke

    vZ = cos(wormAng.x) * cos(wormAng.y) * sila; //* dlugosc sily
    vX = sin(wormAng.x) * cos(wormAng.y) * sila; //
    vY = sin(wormAng.y) * sila; //

    flagaPocisku = 2;
}



glm::vec3 Pocisk::pozycjaPocisku(float czas) {
    glm::vec3 nastepna = glm::vec3(1.0f);
    nastepna.z = poprzednia.z - vZ * czas;
    nastepna.x = poprzednia.x + vX * czas;
    nastepna.y = poprzednia.y + vY * czas - grawitacja / 2 * czas * czas;
    vY = vY - grawitacja * czas;
    poprzednia = nastepna;
    if(heightMap->height(nastepna.x, nastepna.z) - 17 > nastepna.y && flagaPocisku == 2){
        flagaPocisku = 3;
//        printf("juz");
    }
    //if ( flagaPocisku == 1 ) poprzednia = nastepna;
    return nastepna;
}


//application.cpp pocisk w przestrzeni świata?

//application.cpp
//linijka 50
//akcje na myszke zrobić jak akcje na przycisk?



void Pocisk::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    double time1;
    double time2;
    double timePassed;
//    auto myApplication = (Application*)glfwGetWindowUserPointer(window);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        time1 = glfwGetTime();
        flagaPocisku = 1;
        //przekazac ile czasu uplynelo, podobnie jak rotacja na klawisz

    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){

        time2 = glfwGetTime();
        timePassed = time2 - time1;

        sila = sila + stalyPrzyrostSily * timePassed;   //TODO
        if (sila == 2 * maxSila) sila = 0.0;
        else if (sila > maxSila) sila = 2 * maxSila - sila;
        //ustawić flagę i zrobić dwie procedury rysujące (rozgałęzienie) w przypadku jeżeli pocisk będzie
        //przekazać wartości do funkcji pocisku skąd zaczyna
        flagaPocisku = 2;
    }
}

//flaga pocisku:
//0 - brak
//1 - ustawianie sily strzalu
//2 - wystrzel - strzal
//2 - leci - pozycja pocisku
//3 - wybuch
