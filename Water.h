//
// Created by Krzysztof Sychla on 2019-06-21.
//

#ifndef OPENGLSETUP_WATER_H
#define OPENGLSETUP_WATER_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Mesh.h"
#include "MeshFactory.h"
#include "generateHeight.h"

class Water {
public:
    Water(int s);
    Mesh createWater();
private:
    int size;
    glm::vec3 generateNormals(int x, int z);
};


#endif //OPENGLSETUP_WATER_H
