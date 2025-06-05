#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

GLuint loadShaderProgram(const char *vertexPath, const char *fragmentPath);
void checkCompileErrors(GLuint shader, const char *type);

#endif
