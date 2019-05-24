//
// Created by Krzysztof Sychla on 2019-05-24.
//

#ifndef OPENGLSETUP_MESHFACTORY_H
#define OPENGLSETUP_MESHFACTORY_H

#include <glm/glm.hpp>
#include <vector>

class Mesh;

class MeshFactory {
public:
    MeshFactory & addPos(glm::vec3 pos);
    MeshFactory & addCol(glm::vec3 col);
    MeshFactory & addUv(glm::vec2 uv);
    MeshFactory & addNorm(glm::vec3 norm);
    MeshFactory & addInd(unsigned int ind);
    MeshFactory & addInd(unsigned int ind1,
                         unsigned int ind2,
                         unsigned int ind3);

    Mesh create();
private:
    void clearVectors();
    bool dirtyVectors = false;

    std::vector<glm::vec3> Pos;
    std::vector<glm::vec3> Col;
    std::vector<glm::vec2> Uvs;
    std::vector<glm::vec3> Norm;

    std::vector<unsigned int> Indicies;
};



#endif //OPENGLSETUP_MESHFACTORY_H
