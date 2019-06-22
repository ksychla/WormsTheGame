//
// Created by Krzysztof Sychla on 2019-06-03.
//

#ifndef OPENGLSETUP_TERRAIN_H
#define OPENGLSETUP_TERRAIN_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Mesh.h"
#include "MeshFactory.h"
#include "generateHeight.h"
//#include "TerrainVertex.h"

class Terrain {
public:
    Terrain(int gridX, int gridZ, int gridY);

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
    int x;
    int z;
    int maxY;
    generateHeight* height = new generateHeight(20.0);
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
    glm::vec3 normals[10][10];

    glm::vec3 generateNormals(int x, int z);
    float getHeight(int x, int z);
};


#endif //OPENGLSETUP_TERRAIN_H
