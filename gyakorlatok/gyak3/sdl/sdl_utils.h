#ifndef SDL_UTILS_H
#define SDL_UTILS_H


#include <stdbool.h>
#include <SDL.h>

// SDL inicializálása
bool init_sdl();

// SDL ablak és renderer létrehozása
bool create_window_and_renderer(SDL_Window** window, SDL_Renderer** renderer);

// Egéresemények kezelése
void handle_mouse_events(SDL_Event event);

#endif // SDL_UTILS_H