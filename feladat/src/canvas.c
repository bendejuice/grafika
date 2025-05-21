#include "canvas.h"
#include <stdio.h>

void canvas_init(Canvas* canvas) {
    for (int y = 0; y < CANVAS_HEIGHT; ++y) {
        for (int x = 0; x < CANVAS_WIDTH; ++x) {
            canvas->pixels[x][y] = (SDL_Color){255, 255, 255, 255};  // fehér
        }
    }
}

void canvas_render(const Canvas* canvas, SDL_Renderer* renderer) {
    for (int y = 0; y < CANVAS_HEIGHT; ++y) {
        for (int x = 0; x < CANVAS_WIDTH; ++x) {
            SDL_Color color = canvas->pixels[x][y];
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_Rect rect = { x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void canvas_set_pixel(Canvas* canvas, int x, int y, SDL_Color color) {
    if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
        canvas->pixels[x][y] = color;
    }
}

int canvas_save(const Canvas* canvas, const char* filename) {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, CANVAS_WIDTH, CANVAS_HEIGHT, 32,
                                                0x00FF0000,
                                                0x0000FF00,
                                                0x000000FF,
                                                0xFF000000);
    if (!surface) {
        fprintf(stderr, "Nem sikerült létrehozni az SDL_Surface-t: %s\n", SDL_GetError());
        return 0;
    }

    // Kitöltjük a surface pixeleit a canvas színeivel
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            SDL_Color c = canvas->pixels[x][y];
            Uint32 pixel_color = SDL_MapRGBA(surface->format, c.r, c.g, c.b, c.a);
            ((Uint32*)surface->pixels)[y * surface->w + x] = pixel_color;
        }
    }

    if (SDL_SaveBMP(surface, filename) != 0) {
        fprintf(stderr, "Nem sikerült menteni a BMP fájlt: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return 0;
    }

    SDL_FreeSurface(surface);
    return 1;
}

int canvas_load(Canvas* canvas, const char* filename) {
    SDL_Surface* surface = SDL_LoadBMP(filename);
    if (!surface) {
        fprintf(stderr, "Nem sikerült betölteni a BMP fájlt: %s\n", SDL_GetError());
        return 0;
    }

    if (surface->w != CANVAS_WIDTH || surface->h != CANVAS_HEIGHT) {
        fprintf(stderr, "A kép mérete nem megfelelő: %dx%d (elvárt %dx%d)\n", surface->w, surface->h, CANVAS_WIDTH, CANVAS_HEIGHT);
        SDL_FreeSurface(surface);
        return 0;
    }

    // Olvassuk ki a pixeleket és töltsük be a canvasba
    SDL_LockSurface(surface);
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            Uint32* pixels = (Uint32*)surface->pixels;
            Uint32 pixel = pixels[y * surface->w + x];
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
            canvas->pixels[x][y] = (SDL_Color){r, g, b, a};
        }
    }
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);

    return 1;
}
