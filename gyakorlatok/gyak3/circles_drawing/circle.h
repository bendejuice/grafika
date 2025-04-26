#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h> // SDL_Color és SDL_Renderer használatához

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Circle
{
    double x;           // Középpont X koordinátája
    double y;           // Középpont Y koordinátája
    double radius;      // Sugár
    SDL_Color color;    // Kör színe
} Circle;

/**
 * Set the data of the circle
 */
void set_circle_data(Circle* circle, double x, double y, double radius, SDL_Color color);

/**
 * Draw the circle using line segments (polygon approximation)
 * @param num_segments Number of segments to approximate the circle
 */
void draw_circle(SDL_Renderer* renderer, const Circle* circle, int num_segments);

#endif // CIRCLE_H