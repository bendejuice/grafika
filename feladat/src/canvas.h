#ifndef CANVAS_H
#define CANVAS_H

#include <SDL.h>

#define CANVAS_WIDTH 32
#define CANVAS_HEIGHT 32
#define PIXEL_SIZE 20

typedef struct {
    SDL_Color pixels[CANVAS_WIDTH][CANVAS_HEIGHT];
} Canvas;

void canvas_init(Canvas* canvas);
void canvas_render(const Canvas* canvas, SDL_Renderer* renderer);
void canvas_set_pixel(Canvas* canvas, int x, int y, SDL_Color color);

// Új funkciók
int canvas_save(const Canvas* canvas, const char* filename);
int canvas_load(Canvas* canvas, const char* filename);

#endif
