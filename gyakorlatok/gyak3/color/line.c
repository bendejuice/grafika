#include "line.h"
#include <stdio.h>


Line create_line(Point start, Point end, Color color) {
    Line line;
    line.start = start;
    line.end = end;
    line.color = color;
    return line;
}


void print_line(const Line* line) {
    printf("Line:\n");
    printf("  Start: (%.2f, %.2f)\n", line->start.x, line->start.y);
    printf("  End: (%.2f, %.2f)\n", line->end.x, line->end.y);
    printf("  Color: RGB(%d, %d, %d)\n", line->color.red, line->color.green, line->color.blue);
}