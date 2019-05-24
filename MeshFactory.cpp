//
// Created by Krzysztof Sychla on 2019-05-24.
//

#include "MeshFactory.h"

#include "Mesh.h"


MeshFactory & MeshFactory::addPos(glm::vec3 pos) {
    if(dirtyVectors) clearVectors();
    Pos.push_back(pos);
    return *this;
}

MeshFactory & MeshFactory::addCol(glm::vec3 col) {
    if(dirtyVectors) clearVectors();
    Col.push_back(col);
    return *this;
}

MeshFactory & MeshFactory::addUv(glm::vec2 uv) {
    if(dirtyVectors) clearVectors();
    Uvs.push_back(uv);
    return *this;
}

MeshFactory & MeshFactory::addNorm(glm::vec3 norm) {
    if(dirtyVectors) clearVectors();
    Norm.push_back(norm);
    return *this;
}

MeshFactory & MeshFactory::addInd(unsigned int ind) {
    if(dirtyVectors) clearVectors();
    Indicies.push_back(ind);
    return *this;
}

MeshFactory &MeshFactory::addInd(unsigned int ind1, unsigned int ind2, unsigned int ind3) {
    addInd(ind1);
    addInd(ind2);
    addInd(ind3);
    return *this;
}

Mesh MeshFactory::create() {
    dirtyVectors = true;
    return Mesh(Pos, Col, Uvs, Norm, Indicies);
}

void MeshFactory::clearVectors() {
    Pos.clear();
    Col.clear();
    Uvs.clear();
    Norm.clear();
    Indicies.clear();
    dirtyVectors = false;
}