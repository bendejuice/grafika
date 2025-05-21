#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "canvas.h"
#include <stdbool.h>

void handle_input(SDL_Event event, int* running, SDL_Color* current_color, Canvas* canvas, bool erase_mode);

#endif
