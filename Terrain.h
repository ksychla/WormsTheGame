//
// Created by Krzysztof Sychla on 2019-06-03.
//

#ifndef OPENGLSETUP_TERRAIN_H
#define OPENGLSETUP_TERRAIN_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Mesh.h"
#include "MeshFactory.h"

class Terrain {
public:
    Terrain(int gridX, int gridZ);

    Mesh drawTerrain();

    float getSize() const;

    void setSize(float size);

    int getVertexCount() const;

    void setVertexCount(int vertexCount);

    float getX() const;

    void setX(float x);

    float getZ() const;

    void setZ(float z);

private:
    int size;
    int vertexCount;
    float x;
    float z;
//    float **y;
    float y[10][10]={
            {0,0,0,1,1,1,0,0,0,0},
            {0,0,0,1,2,1,0,0,0,0},
            {0,0,1,2,3,2,1,0,0,0},
            {1,1,2,3,4,3,2,1,1,0},
            {1,2,3,4,5,4,3,2,1,0},
            {1,1,2,3,4,3,2,1,1,0},
            {0,0,1,2,3,2,1,0,0,0},
            {0,0,0,1,2,1,0,0,0,0},
            {0,0,0,1,1,1,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0}
    };
};


#endif //OPENGLSETUP_TERRAIN_H
