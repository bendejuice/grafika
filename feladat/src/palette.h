#ifndef PALETTE_H
#define PALETTE_H

#include <SDL.h>

// Alap paletta
SDL_Color get_palette_color(int index);
int palette_color_at_position(int x, int y);
SDL_Color palette_get_default_color(void);
void palette_render(SDL_Renderer* renderer, const SDL_Color* selected_color);

// Új függvények sliderhez
void palette_render_sliders(SDL_Renderer* renderer, SDL_Color* current_color);
int palette_handle_slider_click(int x, int y, SDL_Color* current_color);

#endif
