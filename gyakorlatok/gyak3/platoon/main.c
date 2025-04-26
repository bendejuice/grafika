#include "sdl_utils.h"
#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE_COUNT 100 // Maximális szakaszok száma
#define PALETTE_SIZE 5     // Palettán lévő színek száma

typedef struct {
    int x1, y1; // Szakasz kezdőpontja
    int x2, y2; // Szakasz végpontja
    SDL_Color color; // Szakasz színe
} Line;

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

    Line lines[MAX_LINE_COUNT]; // Szakaszok tömbje
    int line_count = 0;         // Aktuális szakaszok száma
    bool drawing = false;       // Rajzolás állapota
    int start_x = 0, start_y = 0; // Szakasz kezdőpontja
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
                    } else if (line_count < MAX_LINE_COUNT) {
                        // Szakaszt rajzolunk
                        if (!drawing) {
                            start_x = event.button.x;
                            start_y = event.button.y;
                            drawing = true;
                        } else {
                            lines[line_count].x1 = start_x;
                            lines[line_count].y1 = start_y;
                            lines[line_count].x2 = event.button.x;
                            lines[line_count].y2 = event.button.y;
                            lines[line_count].color = active_color;
                            line_count++;
                            drawing = false;
                        }
                    }
                    break;
            }
        }

        // Háttér törlése
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fekete háttér
        SDL_RenderClear(renderer);

        // Szakaszok kirajzolása
        for (int i = 0; i < line_count; i++) {
            draw_line(renderer, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2, lines[i].color);
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

//gcc main.c sdl_utils.c -o line_drawer -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
// ./line_drawer