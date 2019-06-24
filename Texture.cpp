//
// Created by Krzysztof Sychla on 2019-06-21.
//

#include "Texture.h"

Texture::Texture(std::string path) : commonPath(path) {
    std::fstream file(commonPath);
    if(!file.good())
        printf("Can't open file\n");
}

GLuint Texture::readTexture() {
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, commonPath);

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