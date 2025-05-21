#include "pong.h"
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdio.h>

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
    pong->left_score = 0;
    pong->right_score = 0;
}

void update_pong(Pong* pong, double time) { /* ... */ }

void render_pong(Pong* pong)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));

    // Pontszámok
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(pong->width / 4, 30);
    char left_score[32];
    sprintf(left_score, "Left: %d", pong->left_score);
    for (int i = 0; left_score[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, left_score[i]);

    glRasterPos2f(3 * pong->width / 4, 30);
    char right_score[32];
    sprintf(right_score, "Right: %d", pong->right_score);
    for (int i = 0; right_score[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, right_score[i]);
}

void bounce_ball(Pong* pong)
{
    // Ütközési logika
    if (pong->ball.x - pong->ball.radius < 50) {
        if (pong->ball.y >= pong->left_pad.y && pong->ball.y <= pong->left_pad.y + pong->left_pad.height) {
            pong->ball.x = 50 + pong->ball.radius;
            pong->ball.speed_x *= -1;
            pong->ball.rotation_speed += 5.0f;
        } else {
            pong->right_score++;
            pong->ball.x = pong->width / 2;
            pong->ball.y = pong->height / 2;
        }
    }
    if (pong->ball.x + pong->ball.radius > pong->width - 50) {
        if (pong->ball.y >= pong->right_pad.y && pong->ball.y <= pong->right_pad.y + pong->right_pad.height) {
            pong->ball.x = pong->width - 50 - pong->ball.radius;
            pong->ball.speed_x *= -1;
            pong->ball.rotation_speed += 5.0f;
        } else {
            pong->left_score++;
            pong->ball.x = pong->width / 2;
            pong->ball.y = pong->height / 2;
        }
    }
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
        pong->ball.rotation_speed -= 5.0f;
    }
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
        pong->ball.rotation_speed -= 5.0f;
    }
}