#include "sdl_utils.h"
#include <stdio.h>
#include <stdbool.h>

#define MAX_RECT_COUNT 100 // Maximális téglalapok száma
#define PALETTE_SIZE 5     // Palettán lévő színek száma

typedef struct {
    SDL_Rect rect;  // Téglalap adatai
    SDL_Color color; // Téglalap színe
} Rectangle;

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // SDL inicializálása
    if (!init_sdl(&window, &renderer)) {
        return 1;
    }

    // Színek definiálása
    SDL_Color palette_colors[PALETTE_SIZE] = {
        {255, 0, 0, 255},   // Piros
        {0, 255, 0, 255},   // Zöld
        {0, 0, 255, 255},   // Kék
        {255, 255, 0, 255}, // Sárga
        {255, 255, 255, 255} // Fehér
    };

    Rectangle rectangles[MAX_RECT_COUNT]; // Téglalapok tömbje
    int rect_count = 0;                   // Aktuális téglalapok száma
    bool drawing = false;                 // Rajzolás állapota
    int start_x = 0, start_y = 0;         // Téglalap kezdőpontja
    SDL_Color active_color = {255, 255, 255, 255}; // Aktív szín

    int window_width = 800;
    int window_height = 600;
    int palette_height = 50; // Paletta magassága

    // Fő ciklus
    bool running = true;
    SDL_Event event;
    while (running) {
        // Események kezelése
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.y >= window_height - palette_height) {
                        // Palettára kattintottunk
                        int color_index = event.button.x / (window_width / PALETTE_SIZE);
                        active_color = palette_colors[color_index];
                    } else if (rect_count < MAX_RECT_COUNT) {
                        // Téglalapot rajzolunk
                        if (!drawing) {
                            start_x = event.button.x;
                            start_y = event.button.y;
                            drawing = true;
                        } else {
                            // Téglalap adatainak kiszámítása
                            int x = (start_x < event.button.x) ? start_x : event.button.x;
                            int y = (start_y < event.button.y) ? start_y : event.button.y;
                            int w = abs(event.button.x - start_x);
                            int h = abs(event.button.y - start_y);

                            rectangles[rect_count].rect = (SDL_Rect){x, y, w, h};
                            rectangles[rect_count].color = active_color;
                            rect_count++;
                            drawing = false;
                        }
                    }
                    break;
            }
        }

        // Háttér törlése
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fekete háttér
        SDL_RenderClear(renderer);

        // Téglalapok kirajzolása
        for (int i = 0; i < rect_count; i++) {
            draw_rectangle(renderer, rectangles[i].rect, rectangles[i].color);
        }

        // Paletta kirajzolása
        draw_palette(renderer, window_width, window_height, palette_colors, PALETTE_SIZE);

        // Renderelés
        SDL_RenderPresent(renderer);
    }

    // Takarítás
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//gcc main.c sdl_utils.c -o rectangle_drawer -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
//./rectangle_drawer