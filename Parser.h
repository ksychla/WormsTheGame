//
// Created by Krzysztof Sychla on 2019-06-15.
//

#ifndef OPENGLSETUP_PARSER_H
#define OPENGLSETUP_PARSER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stdio.h>
#include <stddef.h>
#include <string>
#include "Mesh.h"
#include "MeshFactory.h"

class Parser {
public:
    Parser();
    ~Parser();
//    void readFile();

    const std::vector<unsigned int> &getVertexIndices() const;

    const std::vector<unsigned int> &getUvIndices() const;

    const std::vector<unsigned int> &getNormalIndices() const;

    bool loadOBJ(const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals);

    Mesh getOBJ(const char * path, glm::vec3);

private:
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    bool flaga;
};


#endif //OPENGLSETUP_PARSER_H
