#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cglm/cglm.h>

// Helper struct for OBJ parsing
typedef struct {
    float position[3];
    float texcoord[2];
    float normal[3]; // Add normal
} VertexData;

int loadOBJ(const char* path, Model* model) {
    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Failed to open OBJ file: %s\n", path);
        return 0;
    }

    vec3 temp_positions[10000];
    vec2 temp_texcoords[10000];
    vec3 temp_normals[10000]; // Store temporary normals
    unsigned int position_count = 0;
    unsigned int texcoord_count = 0;
    unsigned int normal_count = 0;

    // Store indices for final vertex data
    unsigned int vertex_indices[30000]; // Max 10000 faces * 3 vertices
    unsigned int texcoord_indices[30000];
    unsigned int normal_indices[30000];
    unsigned int index_count = 0;

    char line[256]; // Increased line buffer size
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            float x, y, z;
            sscanf(line, "v %f %f %f", &x, &y, &z);
            glm_vec3_copy((vec3){x, y, z}, temp_positions[position_count++]);
        } else if (strncmp(line, "vt ", 3) == 0) {
            float u, v;
            sscanf(line, "vt %f %f", &u, &v);
            glm_vec2_copy((vec2){u, v}, temp_texcoords[texcoord_count++]);
        } else if (strncmp(line, "vn ", 3) == 0) { // Parse normals
            float x, y, z;
            sscanf(line, "vn %f %f %f", &x, &y, &z);
            glm_vec3_copy((vec3){x, y, z}, temp_normals[normal_count++]);
        } else if (strncmp(line, "f ", 2) == 0) {
            unsigned int vi[4], ti[4], ni[4]; // Max 4 vertices per face (quads)
            int matches = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                                 &vi[0], &ti[0], &ni[0],
                                 &vi[1], &ti[1], &ni[1],
                                 &vi[2], &ti[2], &ni[2],
                                 &vi[3], &ti[3], &ni[3]);

            if (matches >= 9) { // Triangle or Quad
                // First triangle
                vertex_indices[index_count] = vi[0] - 1;
                texcoord_indices[index_count] = ti[0] - 1;
                normal_indices[index_count] = ni[0] - 1;
                index_count++;
                vertex_indices[index_count] = vi[1] - 1;
                texcoord_indices[index_count] = ti[1] - 1;
                normal_indices[index_count] = ni[1] - 1;
                index_count++;
                vertex_indices[index_count] = vi[2] - 1;
                texcoord_indices[index_count] = ti[2] - 1;
                normal_indices[index_count] = ni[2] - 1;
                index_count++;

                // If it's a quad, add the second triangle
                if (matches == 12) {
                    vertex_indices[index_count] = vi[0] - 1;
                    texcoord_indices[index_count] = ti[0] - 1;
                    normal_indices[index_count] = ni[0] - 1;
                    index_count++;
                    vertex_indices[index_count] = vi[2] - 1;
                    texcoord_indices[index_count] = ti[2] - 1;
                    normal_indices[index_count] = ni[2] - 1;
                    index_count++;
                    vertex_indices[index_count] = vi[3] - 1;
                    texcoord_indices[index_count] = ti[3] - 1;
                    normal_indices[index_count] = ni[3] - 1;
                    index_count++;
                }
            } else {
                fprintf(stderr, "Unsupported face format in OBJ: %s", line);
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);

    VertexData* vertices = malloc(sizeof(VertexData) * index_count);
    if (!vertices) {
        fprintf(stderr, "Memory allocation failed for vertices.\n");
        return 0;
    }

    for (unsigned int i = 0; i < index_count; i++) {
        memcpy(vertices[i].position, temp_positions[vertex_indices[i]], sizeof(vec3));
        memcpy(vertices[i].texcoord, temp_texcoords[texcoord_indices[i]], sizeof(vec2));
        memcpy(vertices[i].normal, temp_normals[normal_indices[i]], sizeof(vec3));
    }

    glGenVertexArrays(1, &model->VAO);
    glGenBuffers(1, &model->VBO);

    glBindVertexArray(model->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * index_count, vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
    glEnableVertexAttribArray(0);

    // Texcoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, texcoord)));
    glEnableVertexAttribArray(1);

    // Normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(offsetof(VertexData, normal)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    model->vertexCount = index_count;

    free(vertices);
    return 1;
}

void drawModel(const Model* model) {
    glBindVertexArray(model->VAO);
    glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
    glBindVertexArray(0);
}

void freeModel(Model* model) {
    glDeleteVertexArrays(1, &model->VAO);
    glDeleteBuffers(1, &model->VBO);
    if (model->textureID != 0) { // Only delete texture if it was loaded
        glDeleteTextures(1, &model->textureID);
    }
    model->VAO = 0;
    model->VBO = 0;
    model->textureID = 0;
    model->vertexCount = 0;
}
