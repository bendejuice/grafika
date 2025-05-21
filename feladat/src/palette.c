#include "palette.h"
#include "canvas.h"

#define PALETTE_SIZE 6

static SDL_Color palette_colors[PALETTE_SIZE] = {
    {255, 0, 0, 255},    // piros
    {0, 255, 0, 255},    // zöld
    {0, 0, 255, 255},    // kék
    {255, 255, 0, 255},  // sárga
    {0, 255, 255, 255},  // cián
    {0, 0, 0, 255}       // fekete
};

SDL_Color palette_get_default_color(void) {
    return palette_colors[0];
}

SDL_Color get_palette_color(int index) {
    if (index >= 0 && index < PALETTE_SIZE) {
        return palette_colors[index];
    }
    return (SDL_Color){0, 0, 0, 255};
}

int palette_color_at_position(int x, int y) {
    int size = 40;
    int padding = 10;
    int top = CANVAS_HEIGHT * PIXEL_SIZE + padding;
    int bottom = top + size;

    if (y < top || y > bottom) return -1;

    for (int i = 0; i < PALETTE_SIZE; i++) {
        int left = padding + i * (size + padding);
        int right = left + size;

        if (x >= left && x <= right) {
            return i;
        }
    }
    return -1;
}

void palette_render(SDL_Renderer* renderer, const SDL_Color* selected_color) {
    int size = 40;
    int padding = 10;

    for (int i = 0; i < PALETTE_SIZE; i++) {
        SDL_Color c = palette_colors[i];
        SDL_Rect rect = {
            .x = padding + i * (size + padding),
            .y = CANVAS_HEIGHT * PIXEL_SIZE + padding,
            .w = size,
            .h = size
        };

        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
        SDL_RenderFillRect(renderer, &rect);

        if (c.r == selected_color->r &&
            c.g == selected_color->g &&
            c.b == selected_color->b) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

// -------- Új függvények sliderhez -----------

#define SLIDER_WIDTH 200
#define SLIDER_HEIGHT 20
#define SLIDER_PADDING 10
#define SLIDER_X 10
#define SLIDER_Y_START (CANVAS_HEIGHT * PIXEL_SIZE + 60)

void palette_render_sliders(SDL_Renderer* renderer, SDL_Color* current_color) {
    // Slider háttere
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);

    // R (vörös) slider
    SDL_Rect red_bg = {SLIDER_X, SLIDER_Y_START, SLIDER_WIDTH, SLIDER_HEIGHT};
    SDL_RenderFillRect(renderer, &red_bg);

    // R érték jelző
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int red_pos = (int)((current_color->r / 255.0f) * SLIDER_WIDTH);
    SDL_Rect red_slider = {SLIDER_X, SLIDER_Y_START, red_pos, SLIDER_HEIGHT};
    SDL_RenderFillRect(renderer, &red_slider);

    // G (zöld) slider
    SDL_Rect green_bg = {SLIDER_X, SLIDER_Y_START + SLIDER_HEIGHT + SLIDER_PADDING, SLIDER_WIDTH, SLIDER_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
    SDL_RenderFillRect(renderer, &green_bg);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    int green_pos = (int)((current_color->g / 255.0f) * SLIDER_WIDTH);
    SDL_Rect green_slider = {SLIDER_X, SLIDER_Y_START + SLIDER_HEIGHT + SLIDER_PADDING, green_pos, SLIDER_HEIGHT};
    SDL_RenderFillRect(renderer, &green_slider);

    // B (kék) slider
    SDL_Rect blue_bg = {SLIDER_X, SLIDER_Y_START + 2 * (SLIDER_HEIGHT + SLIDER_PADDING), SLIDER_WIDTH, SLIDER_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
    SDL_RenderFillRect(renderer, &blue_bg);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    int blue_pos = (int)((current_color->b / 255.0f) * SLIDER_WIDTH);
    SDL_Rect blue_slider = {SLIDER_X, SLIDER_Y_START + 2 * (SLIDER_HEIGHT + SLIDER_PADDING), blue_pos, SLIDER_HEIGHT};
    SDL_RenderFillRect(renderer, &blue_slider);
}

// Visszatérési érték: 1 ha slider értéket változtatott, 0 ha nem
int palette_handle_slider_click(int x, int y, SDL_Color* current_color) {
    if (x < SLIDER_X || x > SLIDER_X + SLIDER_WIDTH) return 0;

    if (y >= SLIDER_Y_START && y <= SLIDER_Y_START + SLIDER_HEIGHT) {
        // Red slider
        int val = (x - SLIDER_X) * 255 / SLIDER_WIDTH;
        if (val < 0) val = 0;
        if (val > 255) val = 255;
        current_color->r = val;
        return 1;
    }
    if (y >= SLIDER_Y_START + SLIDER_HEIGHT + SLIDER_PADDING &&
        y <= SLIDER_Y_START + SLIDER_HEIGHT + SLIDER_PADDING + SLIDER_HEIGHT) {
        // Green slider
        int val = (x - SLIDER_X) * 255 / SLIDER_WIDTH;
        if (val < 0) val = 0;
        if (val > 255) val = 255;
        current_color->g = val;
        return 1;
    }
    if (y >= SLIDER_Y_START + 2 * (SLIDER_HEIGHT + SLIDER_PADDING) &&
        y <= SLIDER_Y_START + 2 * (SLIDER_HEIGHT + SLIDER_PADDING) + SLIDER_HEIGHT) {
        // Blue slider
        int val = (x - SLIDER_X) * 255 / SLIDER_WIDTH;
        if (val < 0) val = 0;
        if (val > 255) val = 255;
        current_color->b = val;
        return 1;
    }
    return 0;
}
