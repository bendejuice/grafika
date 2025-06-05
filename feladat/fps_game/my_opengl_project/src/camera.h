#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <cglm/cglm.h>

typedef struct {
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
} Camera;

void initCamera(Camera* cam, vec3 position, vec3 up, float yaw, float pitch);
void updateCameraVectors(Camera* cam);
void processKeyboard(Camera* cam, int direction, float deltaTime);
void processMouseMovement(Camera* cam, float xoffset, float yoffset);

#define CAMERA_FORWARD 0
#define CAMERA_BACKWARD 1
#define CAMERA_LEFT 2
#define CAMERA_RIGHT 3

#endif
