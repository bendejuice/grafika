#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>
#include <stdio.h>

// Elavult GLUT figyelmeztetések elnyomása
#define GL_SILENCE_DEPRECATION

void init_game(Game* game, int width, int height) { /* ... */ }

void destroy_game(Game* game) { /* ... */ }

void handle_game_events(Game* game)
{
    SDL_Event event;
    int x, y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // Eseménykezelés...
        }
    }
}

void update_game(Game* game) { /* ... */ }

void render_game(Game* game)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_pong(&(game->pong));
    SDL_GL_SwapWindow(game->window);
}

bool init_sdl(Game* game) { /* ... */ }

void init_opengl(Game* game)
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, game->width, game->height, 0, -200, 200);
    glViewport(0, 0, game->width, game->height);
}