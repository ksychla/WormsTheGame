//
// Created by Krzysztof Sychla on 2019-05-24.
//

#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>

void
ShaderProgram::loadProgram(const char *commonPath, const char *vertex, const char *geometry, const char *fragment) {
    char* vert = nullptr;
    if(vertex != nullptr) {
        vert = new char[100];
        strcpy(vert, commonPath);
        strcat(vert, vertex);
    }

    char* geom = nullptr;
    if(geometry != nullptr) {
        geom = new char[100];
        strcpy(geom, commonPath);
        strcat(geom, geometry);
    }

    char* frag = nullptr;
    if(fragment != nullptr) {
        frag = new char[100];
        strcpy(frag, commonPath);
        strcat(frag, fragment);
    }

    loadProgram(vert, geom, frag);

    if(vertex != nullptr)
        delete [] vert;
    if(geometry != nullptr)
        delete [] geom;
    if(fragment != nullptr)
        delete [] frag;
}

void ShaderProgram::loadProgram(const char *vertex, const char *geometry, const char *fragment) {
    if(vertex == nullptr){
        //TODO: add exception
        std::cerr << "Vertex shader is required for a shader program.\n";
        exit(1);
    }

    freeProgram();

    loadShader(vertex, GL_VERTEX_SHADER);
    loadShader(geometry, GL_GEOMETRY_SHADER);
    loadShader(fragment, GL_FRAGMENT_SHADER);

    consolidateProgram();

    /* After consolidation shader openGL objects are redundant */
    freeShaders();
}

void ShaderProgram::loadShader(const char *path, GLuint shaderType) {
    if(path != nullptr){
        std::string shaderSourceCode = readShaderFile(path);
        GLuint shaderName = glCreateShader(shaderType);

        const char *const_source_code_ptr = shaderSourceCode.c_str();
        glShaderSource(shaderName, 1, &const_source_code_ptr, NULL);
        compileShader(shaderName);

    }
}

std::string ShaderProgram::readShaderFile(const char *path) {
    std::ifstream file(path);
    if (file.is_open()) {
        std::stringstream fileBuffer;
        fileBuffer << file.rdbuf();
        return fileBuffer.str();
    }
    else {
        //TODO: add exception
        std::cerr << "Invalid path " << std::string(path) << "\n" << strerror(errno) <<"\n";
        exit(1);
    }
}

void ShaderProgram::compileShader(GLuint shaderName) {
    glCompileShader(shaderName);

    GLint success = 0;
    glGetShaderiv(shaderName, GL_COMPILE_STATUS, &success);
    if (success != GL_FALSE) {
        shaderNames[numShaders++] = shaderName;
    } else {
        //TODO: add exception
        std::cerr << "=== SHADER COMPILATION ERROR ===\n"
                     + getCompilationLog(shaderName) + "\n";
        exit(1);
    }
}

std::string ShaderProgram::getCompilationLog(GLuint shaderName) const {
    GLint compilationLogSize = 0;
    glGetShaderiv(shaderName, GL_INFO_LOG_LENGTH, &compilationLogSize);
    std::vector<GLchar> compilationLog(compilationLogSize);
    glGetShaderInfoLog(shaderName, compilationLogSize, &compilationLogSize, &compilationLog[0]);
    return std::string(compilationLog.begin(), compilationLog.end());
}

void ShaderProgram::consolidateProgram() {
    programName = glCreateProgram();
    for(int i = 0; i < numShaders; i ++)
        glAttachShader(programName, shaderNames[i]);

    glBindFragDataLocation(programName, 0, "out_Color");

    glLinkProgram(programName);

    GLint status;
    glGetProgramiv(programName, GL_LINK_STATUS, &status);
    if(status == GL_FALSE){
        //TODO: add exception
        std::cerr << "=== SHADER PROGRAM CONSOLIDATION ERROR ===\n"
                     + getProgramConsolidationLog() + "\n";
        exit(1);
    }
}

std::string ShaderProgram::getProgramConsolidationLog() const {
    GLint consolidationLogSize;

    glGetProgramiv(programName, GL_INFO_LOG_LENGTH, &consolidationLogSize);

    std::vector<GLchar> consolidationLog(consolidationLogSize);
    glGetProgramInfoLog(programName, consolidationLogSize, &consolidationLogSize, &consolidationLog[0]);

    return std::string(consolidationLog.begin(), consolidationLog.end());
}

void ShaderProgram::freeShaders() {
    while(numShaders > 0)
        glDeleteShader(shaderNames[--numShaders]);
}

void ShaderProgram::freeProgram() {
    glDeleteProgram(programName);
}

GLint ShaderProgram::getU(const std::string uniformName) {
    GLint uniformLocation = 0;
    auto locationContainer = uniformLocationsMap.find(uniformName);
    if(locationContainer == uniformLocationsMap.end()){
        uniformLocation = glGetUniformLocation(programName, uniformName.c_str());
        uniformLocationsMap.emplace(uniformName, uniformLocation);
    }
    else {
        uniformLocation = locationContainer->second;
    }
    return uniformLocation;
}
