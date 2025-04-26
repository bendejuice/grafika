#include "sdl_utils.h"
#include <stdio.h>
#include <SDL.h>

// SDL inicializálása
bool init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL inicializálás sikertelen: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

// Ablak és renderer létrehozása
bool create_window_and_renderer(SDL_Window** window, SDL_Renderer** renderer) {
    *window = SDL_CreateWindow(
        "Egér pozíció kiíratása", // Ablak címe
        SDL_WINDOWPOS_CENTERED,   // X pozíció
        SDL_WINDOWPOS_CENTERED,   // Y pozíció
        800,                      // Ablak szélessége
        600,                      // Ablak magassága
        SDL_WINDOW_SHOWN          // Ablak flag-ek
    );

    if (*window == NULL) {
        printf("Ablak létrehozása sikertelen: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Renderer létrehozása sikertelen: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// Egéresemények kezelése
void handle_mouse_events(SDL_Event event) {
    if (event.type == SDL_MOUSEMOTION) {
        int mouse_x = event.motion.x;
        int mouse_y = event.motion.y;
        printf("Egér pozíció: (%d, %d)\n", mouse_x, mouse_y);
    }
}