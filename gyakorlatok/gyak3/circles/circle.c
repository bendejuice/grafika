#include "circle.h"
#include <math.h>

void set_circle_data(Circle* circle, double x, double y, double radius, SDL_Color color)
{
    circle->x = x;
    circle->y = y;
    circle->color = color; // Szín beállítása
    if (radius > 0.0) {
        circle->radius = radius;
    } else {
        circle->radius = NAN;
    }
}

double calc_circle_area(const Circle* circle)
{
    double area = circle->radius * circle->radius * M_PI;
    return area;
}

// Körvonal kirajzolása szakaszokkal (lépések száma alapján)
void draw_circle_with_segments(SDL_Renderer* renderer, const Circle* circle, int num_segments)
{
    double angle_step = 2 * M_PI / num_segments; // Szöglépés
    double angle = 0.0;

    // Körvonal pontjainak kiszámítása és összekötése
    for (int i = 0; i < num_segments; i++) {
        double x1 = circle->x + circle->radius * cos(angle);
        double y1 = circle->y + circle->radius * sin(angle);
        angle += angle_step;
        double x2 = circle->x + circle->radius * cos(angle);
        double y2 = circle->y + circle->radius * sin(angle);

        // Szakasz kirajzolása
        SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, circle->color.a);
        SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    }
}

// Körvonal kirajzolása szakaszokkal (lépések szöge alapján)
void draw_circle_with_angle_step(SDL_Renderer* renderer, const Circle* circle, double angle_step)
{
    double angle = 0.0;

    // Körvonal pontjainak kiszámítása és összekötése
    while (angle < 2 * M_PI) {
        double x1 = circle->x + circle->radius * cos(angle);
        double y1 = circle->y + circle->radius * sin(angle);
        angle += angle_step;
        double x2 = circle->x + circle->radius * cos(angle);
        double y2 = circle->y + circle->radius * sin(angle);

        // Szakasz kirajzolása
        SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, circle->color.a);
        SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    }
}

// Körvonal kirajzolása szakaszokkal (szakaszok maximális hossza alapján)
void draw_circle_with_max_segment_length(SDL_Renderer* renderer, const Circle* circle, double max_segment_length)
{
    // Szükséges szöglépés kiszámítása
    double angle_step = 2 * asin(max_segment_length / (2 * circle->radius));
    double angle = 0.0;

    // Körvonal pontjainak kiszámítása és összekötése
    while (angle < 2 * M_PI) {
        double x1 = circle->x + circle->radius * cos(angle);
        double y1 = circle->y + circle->radius * sin(angle);
        angle += angle_step;
        double x2 = circle->x + circle->radius * cos(angle);
        double y2 = circle->y + circle->radius * sin(angle);

        // Szakasz kirajzolása
        SDL_SetRenderDrawColor(renderer, circle->color.r, circle->color.g, circle->color.b, circle->color.a);
        SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    }
}