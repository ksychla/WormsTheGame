//
// Created by Krzysztof Sychla on 2019-06-03.
//

#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ) {
    size = 10;
    vertexCount = 128;
    x = gridX;
    z = gridZ;
//    y = new float *[size];
//    for(int i=0;i<size;i++){
//        y[i] = new float[size];
//    }

}

Mesh Terrain::drawTerrain() {
    MeshFactory m;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            m = m.addPos(glm::vec3(i*x, y[i][j], j*z));
            m = m.addCol(glm::vec3(0.34, 0.49, 0.27));
        }
    }
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-1;j++) {
            m = m.addInd(i*size+j,i*size+j+1,i*size+j+size);
            m = m.addInd(i*size+j+size,i*size+j+size+1,i*size+j+1);
        }
    }

    Mesh terrain = m.create();
    return terrain;

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
