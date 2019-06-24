//
// Created by Krzysztof Sychla on 2019-06-23.
//

#ifndef OPENGLSETUP_GAME_H
#define OPENGLSETUP_GAME_H


class Game {
public:
    Game();
    ~Game();

    int getHealthRed() const;

    void setHealthRed(int healthRed);

    int getHealthBlue() const;

    void setHealthBlue(int healthBlue);

    int getCzasRozgrywki() const;

    void setCzasRozgrywki(int czasRozgrywki);

private:
    int healthRed;
    int healthBlue;
    int czasRozgrywki;   // ??
    float wiatr;
    float maxWiatr;
};


#endif //OPENGLSETUP_GAME_H
