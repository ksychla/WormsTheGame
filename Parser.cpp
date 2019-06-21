//
// Created by Krzysztof Sychla on 2019-06-15.
//

#include "Parser.h"

Parser::Parser(const char* path) {

}

void Parser::readFile() {

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
