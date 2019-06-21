//
// Created by Krzysztof Sychla on 2019-06-21.
//

#ifndef OPENGLSETUP_GENERATEHEIGHT_H
#define OPENGLSETUP_GENERATEHEIGHT_H

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>

class generateHeight {
public:
    generateHeight(float amplituda);

    float height(int x, int z);

private:
    float amplituda;
    int seed;

    float getNoise(int x, int z);
    float getSmoothNoise(int x, int z);
    float cosineInterpolation(float a, float b, float blend);
    float getInterpolatedNoise(float x, float z);

};


#endif //OPENGLSETUP_GENERATEHEIGHT_H
