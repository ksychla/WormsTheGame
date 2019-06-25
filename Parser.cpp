//
// Created by Krzysztof Sychla on 2019-06-15.
//

#include "Parser.h"

Parser::Parser() {

}

//void Parser::readFile() {
//
//}

bool Parser::loadOBJ(const char *path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs,
                     std::vector<glm::vec3> &out_normals) {
    FILE * file = fopen(path, "r");
    if( file == nullptr ){
        printf("Impossible to open the file !\n");
        return false;
    }
    flaga = false;
    while( 1 ) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader
        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2],
                                 &normalIndex[2]);
            if (matches != 9) {
                printf("Cannot read file\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        out_vertices.push_back(vertex);
    }
    if(!flaga)
        for( unsigned int i=0; i<uvIndices.size(); i++ ){
            unsigned int vertexIndex = uvIndices[i];
            glm::vec2 uvs = temp_uvs[ vertexIndex-1 ];
            out_uvs.push_back(uvs);
        }
    for( unsigned int i=0; i<normalIndices.size(); i++ ){
        unsigned int vertexIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[ vertexIndex-1 ];
        out_normals.push_back(normal);
    }
}

Mesh Parser::getOBJ(const char * path, glm::vec3 col){
    MeshFactory obj;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;
    bool res = loadOBJ(path, vertices, uvs, normals);

    for(auto i : vertices){
        obj = obj.addPos(i);
    }
    if(!uvs.empty())
        for(auto i : uvs){
            obj = obj.addUv(i);
        }
    for(auto i : normals){
        obj = obj.addNorm(i);
    }

    int j = 0;
    for(auto i : vertices){
        obj = obj.addInd(j++)
                .addCol(col);
    }

    return obj.create();

}

const std::vector<unsigned int> &Parser::getVertexIndices() const {
    return vertexIndices;
}

const std::vector<unsigned int> &Parser::getUvIndices() const {
    return uvIndices;
}

const std::vector<unsigned int> &Parser::getNormalIndices() const {
    return normalIndices;
}
