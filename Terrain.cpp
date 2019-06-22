//
// Created by Krzysztof Sychla on 2019-06-03.
//

#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, int gridY) {
    size = 50;
    vertexCount = 128;
    x = gridX;
    z = gridZ;
    maxY = gridY;


}

Mesh Terrain::drawTerrain() {
    MeshFactory m;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            m = m.addPos(glm::vec3(i*x, getHeight(i,j), j*z))
                 .addCol(glm::vec3(0.34, 0.49, 0.27))
                 .addNorm(generateNormals(i,j));
        }
    }
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-1;j++) {
            m = m.addInd(i*size+j,i*size+j+1,i*size+j+size)
                 .addInd(i*size+j+size,i*size+j+size+1,i*size+j+1);
        }
    }


    Mesh terrain = m.create();
    return terrain;

}

glm::vec3 Terrain::generateNormals(int x, int z){
    float hL = getHeight(x-1, z);
    float hR = getHeight(x+1, z);
    float hD = getHeight(x, z-1);
    float hU = getHeight(x, z+1);
    glm::vec3 vector = glm::vec3(hL-hR, 2.0f, hD-hU);
    glm::normalize(vector);
    return vector;
}

float Terrain::getHeight(int x, int z) {
    return height->height(x,z);
}

float Terrain::getSize() const {
    return size;
}

void Terrain::setSize(float size) {
    Terrain::size = size;
}

int Terrain::getVertexCount() const {
    return vertexCount;
}

void Terrain::setVertexCount(int vertexCount) {
    Terrain::vertexCount = vertexCount;
}

float Terrain::getX() const {
    return x;
}

void Terrain::setX(float x) {
    Terrain::x = x;
}

float Terrain::getZ() const {
    return z;
}

void Terrain::setZ(float z) {
    Terrain::z = z;
}
