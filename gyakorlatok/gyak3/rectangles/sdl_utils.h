#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL.h>
#include <stdbool.h>

// Ablak és renderer inicializálása
bool init_sdl(SDL_Window** window, SDL_Renderer** renderer);

// Szakasz kirajzolása (színnel)
// void draw_line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color);

// Téglalap kirajzolása (színnel)
void draw_rectangle(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

// Paletta kirajzolása
void draw_palette(SDL_Renderer* renderer, int window_width, int window_height, SDL_Color* colors, int palette_size);

#endif // SDL_UTILS_H