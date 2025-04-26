#include "sdl_utils.h"

#include <stdbool.h>
#include <SDL.h>

int main() {
    // SDL inicializálása
    if (!init_sdl()) {
        return 1;
    }

    // Ablak és renderer létrehozása
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (!create_window_and_renderer(&window, &renderer)) {
        SDL_Quit();
        return 1;
    }

    // Fő ciklus
    bool running = true;
    SDL_Event event;
    while (running) {
        // Események kezelése
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            // Egéresemények kezelése
            handle_mouse_events(event);
        }

        // Renderelés
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Háttérszín beállítása (fekete)
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // Takarítás
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}   