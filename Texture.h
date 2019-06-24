//
// Created by Krzysztof Sychla on 2019-06-21.
//

#ifndef OPENGLSETUP_TEXTURE_H
#define OPENGLSETUP_TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <fstream>
#include "lodepng.h"

class Texture {
public:
    Texture(std::string path);
    GLuint readTexture();
private:
    std::string commonPath;
    GLuint texture;
};


#endif //OPENGLSETUP_TEXTURE_H
