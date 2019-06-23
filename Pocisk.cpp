//
// Created by Krzysztof Sychla on 2019-06-21.
//

#include "Pocisk.h"

void Pocisk::strzal(glm::vec3 posStart) {
    wormPos = posStart; //tu przypisać pozycje robaka, x, y, z //pierwsza pozycja pocisku
    wormAng = glm::vec2(0.0f, 0.0f); //kąt względem x?, kąt góra-dół (oś z)

//    sila? //sile tez by mozna bylo przekazać, robić ją jak dlugo trzyma sie myszke

    vX = cos(wormAng.x) * cos(wormAng.y) * sila; //* dlugosc sily
    vY = sin(wormAng.x) * cos(wormAng.y) * sila; //
    vZ = sin(wormAng.y) * sila; //

    flagaPocisku = 2;
}



glm::vec4 Pocisk::pozycjaPocisku(glm::vec4 poprzednia, float czas) {
    glm::vec4 nastepna = glm::vec4(1.0f);
    nastepna.x = poprzednia.x + vX * czas;
    nastepna.y = poprzednia.y + vY * czas;
    nastepna.z = poprzednia.z + vZ * czas - grawitacja / 2 * czas * czas;
    vZ = vZ - grawitacja * czas;
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
        flagaPocisku = 1;
    }
}

//flaga pocisku:
//0 - brak
//1 - wystrzel - strzal
//2 - leci - pozycja pocisku
//?3 - wybuch? //wybuch w vertex?
