#include "color.h"


Color create_color(unsigned char red, unsigned char green, unsigned char blue) {
    Color color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    return color;
}