#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

typedef struct {
    GLuint VAO;
    GLuint VBO;
    GLuint textureID;
    int vertexCount;
} Model;

int loadOBJ(const char* path, Model* model);
void drawModel(const Model* model);
void freeModel(Model* model);

#endif
