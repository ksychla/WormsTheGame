//
// Created by Krzysztof Sychla on 2019-05-24.
//

#ifndef OPENGLSETUP_SHADERPROGRAM_H
#define OPENGLSETUP_SHADERPROGRAM_H

#include <string>
#include <GL/glew.h>
#include <map>

class ShaderProgram {
public:

    void loadProgram(
            const char* commonPath,
            const char* vertex,
            const char* geometry,
            const char* fragment
    );

    void loadProgram(
            const char* vertex,
            const char* geometry,
            const char* fragment
            );

    void use(){ glUseProgram(programName); }
    void freeProgram();
    GLint getU(const std::string uniformName);

private:
    std::string readShaderFile(const char *path);
    void loadShader(const char *path, GLuint shaderType);
    void compileShader(GLuint shaderName);

    void consolidateProgram();
    void freeShaders();

    GLuint programName = 0;
    int numShaders = 0;
    GLuint shaderNames[3] = {0,0,0};

    std::string getCompilationLog(GLuint shaderName) const;

    std::string getProgramConsolidationLog() const;

    std::map<std::string, GLint> uniformLocationsMap;
};


#endif //OPENGLSETUP_SHADERPROGRAM_H
