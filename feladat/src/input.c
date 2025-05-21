#include "input.h"
#include "palette.h"
#include "canvas.h"
#include <stdbool.h>

void handle_input(SDL_Event event, int* running, SDL_Color* current_color, Canvas* canvas, bool erase_mode) {
    if (event.type == SDL_QUIT) {
        *running = 0;
    } else if (event.type == SDL_MOUSEBUTTONDOWN || 
               (event.type == SDL_MOUSEMOTION && (event.motion.state & SDL_BUTTON_LMASK))) {

        int x = (event.type == SDL_MOUSEBUTTONDOWN) ? event.button.x : event.motion.x;
        int y = (event.type == SDL_MOUSEBUTTONDOWN) ? event.button.y : event.motion.y;

        // Először slider ellenőrzése (RGB slider)
        if (palette_handle_slider_click(x, y, current_color)) {
            return;
        }

        // Ha a vászon alatt vagyunk, paletta színt választunk
        if (y >= CANVAS_HEIGHT * PIXEL_SIZE) {
            int index = palette_color_at_position(x, y);
            if (index != -1) {
                *current_color = get_palette_color(index);
            }
        } else {
            SDL_Color draw_color = erase_mode ? (SDL_Color){255, 255, 255, 255} : *current_color;
            int pixel_x = x / PIXEL_SIZE;
            int pixel_y = y / PIXEL_SIZE;
            canvas_set_pixel(canvas, pixel_x, pixel_y, draw_color);
        }
    }
}
