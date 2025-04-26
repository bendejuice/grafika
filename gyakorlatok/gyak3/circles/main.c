#include "circle.h"
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    // SDL inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL inicializálás sikertelen: %s\n", SDL_GetError());
        return 1;
    }

    // Ablak létrehozása
    SDL_Window* window = SDL_CreateWindow(
        "Circle Drawing",          // Ablak címe
        SDL_WINDOWPOS_CENTERED,    // X pozíció
        SDL_WINDOWPOS_CENTERED,    // Y pozíció
        800,                       // Ablak szélessége
        600,                       // Ablak magassága
        SDL_WINDOW_SHOWN           // Ablak flag-ek
    );

    if (window == NULL) {
        printf("Ablak létrehozása sikertelen: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Renderer létrehozása
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer létrehozása sikertelen: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Kör létrehozása
    Circle circle;
    SDL_Color color = {255, 0, 0, 255}; // Piros szín
    set_circle_data(&circle, 400, 300, 100, color); // Középpont: (400, 300), sugár: 100

    // Fő ciklus
    bool running = true;
    SDL_Event event;
    while (running) {
        // Események kezelése
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Háttér törlése
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fekete háttér
        SDL_RenderClear(renderer);

        // Kör kirajzolása különböző módszerekkel
        // Válaszd ki az egyik módszert a kipróbáláshoz:

        // 1. Lépések száma alapján
        draw_circle_with_segments(renderer, &circle, 100); // 100 szakasszal közelítjük

        // 2. Lépések szöge alapján
        // draw_circle_with_angle_step(renderer, &circle, M_PI / 20); // Lépések szöge: π/20

        // 3. Szakaszok maximális hossza alapján
        // draw_circle_with_max_segment_length(renderer, &circle, 5.0); // Szakaszok maximális hossza: 5.0

        // Renderelés
        SDL_RenderPresent(renderer);
    }

    // Takarítás
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


//gcc main.c circle.c -o circle_drawer -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lm
//./circle_drawer
