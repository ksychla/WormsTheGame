//
// Created by Krzysztof Sychla on 2019-06-21.
//

#include "Water.h"

Water::Water(int s) {
    size = s;
}

Mesh Water::createWater() {
    MeshFactory m;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            m = m.addPos(glm::vec3(i-size/2, 0.0, j-size/2))
                    .addCol(glm::vec3(0.f, 0.f, 0.9))
                    .addNorm(glm::vec3(0.0, 2.0, 0.0));
        }
    }
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-1;j++) {
            m = m.addInd(i*size+j,i*size+j+1,i*size+j+size)
                    .addInd(i*size+j+size,i*size+j+size+1,i*size+j+1);
        }
    }


    Mesh water = m.create();
    return water;
}

