#include "line.h"

int main() {
    
    Point start = create_point(0.0f, 0.0f);
    Point end = create_point(1.0f, 1.0f);

   
    Color red = create_color(255, 0, 0);

    
    Line line = create_line(start, end, red);

   
    print_line(&line);

    return 0;
}