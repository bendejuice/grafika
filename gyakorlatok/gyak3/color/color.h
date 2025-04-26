#ifndef COLOR_H
#define COLOR_H


typedef struct {
    unsigned char red;   
    unsigned char green; 
    unsigned char blue;  
} Color;


Color create_color(unsigned char red, unsigned char green, unsigned char blue);

#endif 