//
// Created by Krzysztof Sychla on 2019-06-21.
//

#include "Pocisk.h"

void Pocisk::strzal(){
    wormPos = glm::vec3(0.0f, 0.0f, 0.0f); //tu przypisać pozycje robaka, x, y, z //pierwsza pozycja pocisku
    wormAng = glm::vec2(0.0f, 0.0f); //kąt względem x?, kąt góra-dół (oś z)

//    sila? //sile tez by mozna bylo przekazać, robić ją jak dlugo trzyma sie myszke

    vX = cos(wormAng.x) * cos(wormAng.y) * sila; //* dlugosc sily
    vY = sin(wormAng.x) * cos(wormAng.y) * sila; //
    vZ = sin(wormAng.y) * sila; //

    flagaPocisku = 2;
}

/*

glm::vec4 Pocisk::pozycjaPocisku(glm::vec4 poprzednia, double czas){
    double grawitacja = 10.0f;
    nastepna = glm::vec4(1.0f);
    nastepna.x = poprzednia.x + vX*czas;
    nastepna.y = poprzednia.y + vY*czas;
    nastepna.z = poprzednia.z + vZ*czas - g/2 * czas^2;
    vZ = vZ - g * czas;
    return nastepna;
}
 */

//application.cpp pocisk w przestrzeni świata?

//application.cpp
//linijka 50
//akcje na myszke zrobić jak akcje na przycisk?


/*
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto myApplication = (Application*)glfwGetWindowUserPointer(window);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        //przekazac ile czasu uplynelo, podobnie jak rotacja na klawisz
        double sila = siła + stałyPrzyrostSiły * timePassed;
        if (sila == 2 * maksymalnaSila) sila = 0.0;
        else if (sila > maksymalnaSila) sila = 2 * maksymalnaSila - sila;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        //ustawić flagę i zrobić dwie procedury rysujące (rozgałęzienie) w przypadku jeżeli pocisk będzie
        //przekazać wartości do funkcji pocisku skąd zaczyna
        flagaPocisku = 1;
    }
}
 */

//flaga pocisku:
//0 - brak
//1 - wystrzel - strzal
//2 - leci - pozycja pocisku
//?3 - wybuch? //wybuch w vertex?
