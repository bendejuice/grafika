#include "camera.h"
#include <math.h>
#include <stdio.h> // For debugging

void initCamera(Camera* cam, vec3 position, vec3 up, float yaw, float pitch) {
    glm_vec3_copy(position, cam->position);
    glm_vec3_copy(up, cam->worldUp);
    cam->yaw = yaw;
    cam->pitch = pitch;
    cam->movementSpeed = 3.0f; // Default speed
    cam->mouseSensitivity = 0.1f;
    updateCameraVectors(cam);
}

void updateCameraVectors(Camera* cam) {
    vec3 front;
    front[0] = cos(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    front[1] = sin(glm_rad(cam->pitch));
    front[2] = sin(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    glm_vec3_normalize_to(front, cam->front);

    glm_vec3_cross(cam->front, cam->worldUp, cam->right);
    glm_vec3_normalize(cam->right);

    glm_vec3_cross(cam->right, cam->front, cam->up);
    glm_vec3_normalize(cam->up);
}

void processKeyboard(Camera* cam, int direction, float deltaTime) {
    float velocity = cam->movementSpeed * deltaTime;
    vec3 temp;
    if (direction == CAMERA_FORWARD) {
        glm_vec3_scale(cam->front, velocity, temp);
        glm_vec3_add(cam->position, temp, cam->position);
    }
    if (direction == CAMERA_BACKWARD) {
        glm_vec3_scale(cam->front, velocity, temp);
        glm_vec3_sub(cam->position, temp, cam->position);
    }
    if (direction == CAMERA_LEFT) {
        glm_vec3_scale(cam->right, velocity, temp);
        glm_vec3_sub(cam->position, temp, cam->position);
    }
    if (direction == CAMERA_RIGHT) {
        glm_vec3_scale(cam->right, velocity, temp);
        glm_vec3_add(cam->position, temp, cam->position);
    }
    // Keep camera at a fixed height (e.g., 1.0f above ground)
    cam->position[1] = 1.0f;
}

void processMouseMovement(Camera* cam, float xoffset, float yoffset) {
    xoffset *= cam->mouseSensitivity;
    yoffset *= cam->mouseSensitivity;

    cam->yaw += xoffset;
    cam->pitch += yoffset;

    if (cam->pitch > 89.0f)
        cam->pitch = 89.0f;
    if (cam->pitch < -89.0f)
        cam->pitch = -89.0f;

    updateCameraVectors(cam);
}