//
// Created by Krzysztof Sychla on 2019-06-21.
//

#include "generateHeight.h"

generateHeight::generateHeight(float amplituda) : amplituda(amplituda) {
    srand(time(NULL));
    seed = rand()%100000000;
}

float generateHeight::height(int x, int z) {
    float total = getInterpolatedNoise(x/8.f,z/8.f) * amplituda;
    total += getInterpolatedNoise(x/4.f,z/4.f) * amplituda / 3.f;
    return total;
}

float generateHeight::getNoise(int x, int z) {
    srand(x * 17788 + z * 35267 + seed);
    float a = ((float)(rand()%10000)/10000);
    srand(time(NULL));
    return a;
}

float generateHeight::getSmoothNoise(int x, int z){
    float corners = (getNoise(x-1,z-1) + getNoise(x+1,z-1) + getNoise(x+1,z+1) + getNoise(x-1,z+1)) / 16;
    float side = (getNoise(x,z-1) + getNoise(x+1,z) + getNoise(x,z+1) + getNoise(x-1,z)) / 8;
    float middle = getNoise(x,z) / 4;
    return corners + side + middle;
}

float generateHeight::cosineInterpolation(float a, float b, float blend){
    double theta = blend * 3.141592;
    float f = (float)(1.f-cos(theta)) * 0.5f;
    return a * (1.f-f) + b * f;
}

float generateHeight::getInterpolatedNoise(float x, float z){
    int intX = (int) x;
    int intZ = (int) z;
    float fracX = x - intX;
    float fracZ = z - intZ;
    float v1 = getSmoothNoise(intX, intZ);
    float v2 = getSmoothNoise(intX + 1, intZ);
    float v3 = getSmoothNoise(intX, intZ + 1);
    float v4 = getSmoothNoise(intX + 1, intZ + 1);
    float i1 = cosineInterpolation(v1, v2, fracX);
    float i2 = cosineInterpolation(v3, v4, fracZ);
    return cosineInterpolation(i1,i2, fracZ);
}