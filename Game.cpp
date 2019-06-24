//
// Created by Krzysztof Sychla on 2019-06-23.
//

#include "Game.h"

Game::Game(){
    healthBlue = healthRed = 100;
}

Game::~Game(){

}

int Game::getHealthRed() const {
    return healthRed;
}

void Game::setHealthRed(int healthRed) {
    Game::healthRed = healthRed;
}

int Game::getHealthBlue() const {
    return healthBlue;
}

void Game::setHealthBlue(int healthBlue) {
    Game::healthBlue = healthBlue;
}

int Game::getCzasRozgrywki() const {
    return czasRozgrywki;
}

void Game::setCzasRozgrywki(int czasRozgrywki) {
    Game::czasRozgrywki = czasRozgrywki;
}
