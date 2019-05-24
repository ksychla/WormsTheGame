//
// Created by Krzysztof Sychla on 2019-05-24.
//

#ifndef OPENGLSETUP_MESH_H
#define OPENGLSETUP_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh {
    friend class MeshFactory;
public:
    virtual ~Mesh();;

    void bind() { glBindVertexArray(vao); }
    void unbind() { glBindVertexArray(0); }

    unsigned int getVertexCount() const { return vertexCount; }

    bool HasPos() const { return !pos.empty(); }

    bool HasCol() const { return !col.empty(); }

    bool HasUvs() const { return !uvs.empty(); }

    bool HasNorm() const { return !norm.empty(); }

    bool HasIndicies() const { return !indicies.empty(); }

    const unsigned int * getIndicies() const { return indicies.data(); }

    unsigned int getIndiciesCount() const { return static_cast<unsigned int>(indicies.size()); }

private:
    Mesh(const std::vector<glm::vec3> &pos, const std::vector<glm::vec3> &col, const std::vector<glm::vec2> &uvs,
         const std::vector<glm::vec3> &norm, const std::vector<unsigned int> &indicies);

    GLuint vao,vbo[5];

    unsigned int vertexCount;

    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> col;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> norm;
    std::vector<unsigned int> indicies;

    const unsigned int posVB  = 0;
    const unsigned int colVB  = 1;
    const unsigned int uvsVB  = 2;
    const unsigned int normVB = 3;
    const unsigned int indVB  = 4;
};


#endif //OPENGLSETUP_MESH_H
