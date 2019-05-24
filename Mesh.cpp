//
// Created by Krzysztof Sychla on 2019-05-24.
//

#include "Mesh.h"

#include <iostream>

template<typename T>
size_t vectorsizeof(const typename std::vector<T>& vec)
{
    return sizeof(T) * vec.size();
}

Mesh::Mesh(const std::vector <glm::vec3> &pos, const std::vector <glm::vec3> &col,
           const std::vector <glm::vec2> &uvs, const std::vector <glm::vec3> &norm,
           const std::vector<unsigned int> &indicies) : pos(pos), col(col), uvs(uvs), norm(norm),
                                                        indicies(indicies) {
    if(!HasPos()){
        //TODO: make exception
        std::cerr << "Can't create a mesh without any positions.\n";
        exit(1);
    }

    vertexCount = static_cast<unsigned int>(pos.size());
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(5, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[posVB]);
    glBufferData(GL_ARRAY_BUFFER, vectorsizeof(pos), pos.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0 );
    glEnableVertexAttribArray(posVB);

    if(HasCol()) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[colVB]);
        glBufferData(GL_ARRAY_BUFFER, vectorsizeof(col), col.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0 );
        glEnableVertexAttribArray(colVB);
    }

    if(HasUvs()){
        glBindBuffer(GL_ARRAY_BUFFER, vbo[uvsVB]);
        glBufferData(GL_ARRAY_BUFFER, vectorsizeof(uvs), uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0 );
        glEnableVertexAttribArray(uvsVB);
    }

    if(HasNorm()){
        glBindBuffer(GL_ARRAY_BUFFER, vbo[normVB]);
        glBufferData(GL_ARRAY_BUFFER, vectorsizeof(norm), norm.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0 );
        glEnableVertexAttribArray(normVB);
    }

    if(HasIndicies()){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[indVB]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vectorsizeof(indicies), indicies.data(), GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(5,vbo);
}

void Mesh::bind() { glBindVertexArray(vao); }

void Mesh::unbind() { glBindVertexArray(0); }

void Mesh::bindPos() { glBindVertexArray(vao);
    glEnableVertexAttribArray(posVB);
    glBindVertexArray(0);
}

void Mesh::unbindPos() { glBindVertexArray(vao);
    glDisableVertexAttribArray(posVB);
    glBindVertexArray(0);
}

void Mesh::bindCol() { glBindVertexArray(vao);
    glEnableVertexAttribArray(colVB);
    glBindVertexArray(0);
}

void Mesh::unbindCol() { glBindVertexArray(vao);
    glDisableVertexAttribArray(colVB);
    glBindVertexArray(0);
}

void Mesh::bindNorm() { glBindVertexArray(vao);
    glEnableVertexAttribArray(normVB);
    glBindVertexArray(0);
}

void Mesh::unbindNorm() { glBindVertexArray(vao);
    glDisableVertexAttribArray(normVB);
    glBindVertexArray(0);
}

void Mesh::bindUvs() { glBindVertexArray(vao);
    glEnableVertexAttribArray(uvsVB);
    glBindVertexArray(0);
}

void Mesh::unbindUvs() { glBindVertexArray(vao);
    glDisableVertexAttribArray(uvsVB);
    glBindVertexArray(0);
}
