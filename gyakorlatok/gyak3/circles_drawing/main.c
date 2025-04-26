#include "circle.h"
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CIRCLE_COUNT 100 // Maximális körök száma
#define PALETTE_SIZE 5       // Palettán lévő színek száma

// Függvény a + jel kirajzolásához
void draw_plus(SDL_Renderer* renderer, int center_x, int center_y, int size, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    // Függőleges vonal
    SDL_RenderDrawLine(renderer, center_x, center_y - size, center_x, center_y + size);
    // Vízszintes vonal
    SDL_RenderDrawLine(renderer, center_x - size, center_y, center_x + size, center_y);
}

int main(int argc, char* argv[])
{
    // SDL inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL inicializálás sikertelen: %s\n", SDL_GetError());
        return 1;
    }

    // Ablak létrehozása
    SDL_Window* window = SDL_CreateWindow(
        "Colorful Circles",       // Ablak címe
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

    // Színek definiálása a palettához
    SDL_Color palette_colors[PALETTE_SIZE] = {
        {255, 0, 0, 255},   // Piros
        {0, 255, 0, 255},   // Zöld
        {0, 0, 255, 255},   // Kék
        {255, 255, 0, 255}, // Sárga
        {255, 255, 255, 255} // Fehér
    };

    // Körök tömbje
    Circle circles[MAX_CIRCLE_COUNT];
    int circle_count = 0; // Aktuális körök száma

    // Aktív szín
    SDL_Color active_color = palette_colors[0]; // Alapértelmezett szín: piros

    int window_width = 800;
    int window_height = 600;
    int palette_height = 50; // Paletta magassága

    // Kör mozgatásához szükséges változók
    int selected_circle_index = -1; // Kijelölt kör indexe (-1: nincs kijelölve)
    int offset_x = 0, offset_y = 0; // Egérkurzor és a kör középpontja közötti eltolás

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
                    } else {
                        // Kör kijelölése vagy új kör rajzolása
                        int mouse_x = event.button.x;
                        int mouse_y = event.button.y;

                        // Ellenőrizzük, hogy az egérkurzor egy körön belül van-e
                        for (int i = 0; i < circle_count; i++) {
                            double distance_squared = (mouse_x - circles[i].x) * (mouse_x - circles[i].x) +
                                                      (mouse_y - circles[i].y) * (mouse_y - circles[i].y);
                            if (distance_squared <= circles[i].radius * circles[i].radius) {
                                // Kör kijelölése
                                selected_circle_index = i;
                                offset_x = mouse_x - circles[i].x;
                                offset_y = mouse_y - circles[i].y;
                                break;
                            }
                        }

                        // Ha nem jelöltünk ki kört, akkor új kört rajzolunk
                        if (selected_circle_index == -1 && circle_count < MAX_CIRCLE_COUNT) {
                            circles[circle_count].x = mouse_x;
                            circles[circle_count].y = mouse_y;
                            circles[circle_count].radius = 50; // Rögzített sugár
                            circles[circle_count].color = active_color;
                            circle_count++;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    // Kör elengedése
                    selected_circle_index = -1;
                    break;

                case SDL_MOUSEMOTION:
                    if (selected_circle_index != -1) {
                        // Kör mozgatása
                        int mouse_x = event.motion.x;
                        int mouse_y = event.motion.y;
                        circles[selected_circle_index].x = mouse_x - offset_x;
                        circles[selected_circle_index].y = mouse_y - offset_y;
                    }
                    break;
            }
        }

        // Háttér törlése
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fekete háttér
        SDL_RenderClear(renderer);

        // Körök kirajzolása
        for (int i = 0; i < circle_count; i++) {
            draw_circle(renderer, &circles[i], 100); // 100 szakasszal közelítjük
        }

        // Egérkurzor pozíciójának lekérése
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        // Ellenőrizzük, hogy az egérkurzor egy körön belül van-e
        for (int i = 0; i < circle_count; i++) {
            double distance_squared = (mouse_x - circles[i].x) * (mouse_x - circles[i].x) +
                                      (mouse_y - circles[i].y) * (mouse_y - circles[i].y);
            if (distance_squared <= circles[i].radius * circles[i].radius) {
                // Ha az egérkurzor a körön belül van, rajzoljunk egy jelet
                draw_plus(renderer, (int)circles[i].x, (int)circles[i].y, 10, (SDL_Color){255, 255, 255, 255}); // + jel
            }
        }

        // Paletta kirajzolása
        for (int i = 0; i < PALETTE_SIZE; i++) {
            SDL_Rect color_rect = {
                i * (window_width / PALETTE_SIZE), // X pozíció
                window_height - palette_height,    // Y pozíció
                window_width / PALETTE_SIZE,       // Szélesség
                palette_height                     // Magasság
            };

            // Szín beállítása
            SDL_SetRenderDrawColor(renderer, palette_colors[i].r, palette_colors[i].g, palette_colors[i].b, palette_colors[i].a);
            SDL_RenderFillRect(renderer, &color_rect); // Négyzet kirajzolása
        }

        // Renderelés
        SDL_RenderPresent(renderer);
    }

    // Takarítás
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


//gcc main.c circle.c -o colorful_circles -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lm
//./colorful_circles

