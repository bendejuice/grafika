#include "pad.h"
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>

void init_pad(Pad* pad, float x, float table_height, enum ColorTheme color_theme)
{
    pad->x = x;
    pad->y = 0;
    pad->width = 50;
    pad->height = 120;
    pad->limit = table_height - pad->height;
    pad->speed = 0;
    pad->color_theme = color_theme;
}

void set_pad_position(Pad* pad, float position) { /* ... */ }
void set_pad_speed(Pad* pad, float speed) { /* ... */ }
void update_pad(Pad* pad, double time) { /* ... */ }

void render_pad(Pad* pad)
{
    float x1 = pad->x;
    float x2 = x1 + pad->width;
    float y1 = pad->y;
    float y2 = y1 + pad->height;

    glBegin(GL_QUADS);
    if (pad->color_theme == RED_THEME) {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x1, y1);
        glColor3f(0.8, 0.2, 0.0);
        glVertex2f(x2, y1);
        glColor3f(1.0, 0.4, 0.0);
        glVertex2f(x2, y2);
        glColor3f(0.9, 0.3, 0.0);
        glVertex2f(x1, y2);
    } else {
        glColor3f(0.0, 0.1, 0.0);
        glVertex2f(x1, y1);
        glColor3f(0.0, 0.8, 0.2);
        glVertex2f(x2, y1);
        glColor3f(0.0, 1.0, 0.4);
        glVertex2f(x2, y2);
        glColor3f(0.0, 0.9, 0.2);
        glVertex2f(x1, y2);
    }
    glEnd();
}