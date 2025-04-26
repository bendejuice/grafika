#include "sdl_utils.h"
#include <stdio.h>

// SDL inicializálása és ablak létrehozása
bool init_sdl(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL inicializálás sikertelen: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow(
        "Szakasz rajzoló",          // Ablak címe
        SDL_WINDOWPOS_CENTERED,     // X pozíció
        SDL_WINDOWPOS_CENTERED,     // Y pozíció
        800,                        // Ablak szélessége
        600,                        // Ablak magassága
        SDL_WINDOW_SHOWN            // Ablak flag-ek
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

// Szakasz kirajzolása (színnel)
void draw_line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

// Paletta kirajzolása
void draw_palette(SDL_Renderer* renderer, int window_width, int window_height, SDL_Color* colors, int palette_size) {
    int palette_height = 50; // Paletta magassága
    int color_width = window_width / palette_size; // Színnégyzetek szélessége

    for (int i = 0; i < palette_size; i++) {
        SDL_Rect color_rect = {
            i * color_width,              // X pozíció
            window_height - palette_height, // Y pozíció
            color_width,                  // Szélesség
            palette_height                // Magasság
        };

        // Szín beállítása
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        SDL_RenderFillRect(renderer, &color_rect); // Négyzet kirajzolása
    }
}