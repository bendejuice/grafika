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
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);

/**
 * Draw the circle using line segments (polygon approximation)
 * @param num_segments Number of segments to approximate the circle
 */
void draw_circle_with_segments(SDL_Renderer* renderer, const Circle* circle, int num_segments);

/**
 * Draw the circle using a fixed angle step between points
 * @param angle_step Angle step in radians
 */
void draw_circle_with_angle_step(SDL_Renderer* renderer, const Circle* circle, double angle_step);

/**
 * Draw the circle using a maximum segment length
 * @param max_segment_length Maximum length of a segment
 */
void draw_circle_with_max_segment_length(SDL_Renderer* renderer, const Circle* circle, double max_segment_length);

#endif // CIRCLE_H