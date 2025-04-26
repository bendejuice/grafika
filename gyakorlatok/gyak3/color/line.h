#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "color.h"


typedef struct {
    Point start; 
    Point end;   
    Color color; 
} Line;


Line create_line(Point start, Point end, Color color);
void print_line(const Line* line);

#endif 