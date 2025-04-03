#include "matrix.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
    float b[3][3];
    float c[3][3];
    float e[3][3];

    float transform[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    scale(transform, 2.0f);
    shift(transform, 3.0f, 4.0f);
    rotate(transform, 45.0f);

    float scalar = 1.5f;

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    print_matrix(a);
    print_matrix(b);

    printf("\n");
    
    add_matrices(a, b, c);

    print_matrix(c);

    printf("\n");

    init_identity_matrix(e);

    print_matrix(e);

    printf("\n");

    scalar_multiply(a, scalar);

    print_matrix(a);

    printf("\n");

    multiply_matrices(a, b, c);

    print_matrix(c);

    printf("\n");

    Point point = {2.0f, 3.0f, 1.0f};
    Point transformed_point = transform_point(transform, point);

    printf("Point after transformation: (%f, %f)\n", transformed_point.x, transformed_point.y);

    return 0;
}