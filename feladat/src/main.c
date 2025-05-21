#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#include "canvas.h"
#include "palette.h"
#include "input.h"

#define WINDOW_WIDTH  (CANVAS_WIDTH * PIXEL_SIZE)
#define WINDOW_HEIGHT (CANVAS_HEIGHT * PIXEL_SIZE + 140)  // Növelve a slider hely miatt

void draw_mode_text(SDL_Renderer* renderer, TTF_Font* font, bool erase_mode) {
    const char* text = erase_mode ? "Mode: radir (E)" : "Mode: ecset (B)";
    SDL_Color color = {0, 0, 0, 255};

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = {10, 10, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Pixel Paint",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 18);
    if (!font) {
        SDL_Log("Nem sikerült betölteni a fontot: %s", TTF_GetError());
        return 1;
    }

    Canvas canvas;
    canvas_init(&canvas);

    SDL_Color current_color = palette_get_default_color();
    bool erase_mode = false;

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_b) {
                    erase_mode = false;
                } else if (event.key.keysym.sym == SDLK_e) {
                    erase_mode = true;
                }
            }

            handle_input(event, &running, &current_color, &canvas, erase_mode);
        }

        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
        SDL_RenderClear(renderer);

        canvas_render(&canvas, renderer);
        palette_render(renderer, &current_color);
        palette_render_sliders(renderer, &current_color);  // Új slider rajzolás
        draw_mode_text(renderer, font, erase_mode);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
