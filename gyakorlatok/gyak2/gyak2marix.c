#include "matrix.h"

#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846




void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}


void init_identity_matrix(float matrix[3][3]){
    int i;
    int j;

    for( i = 0; i < 3; i++){
        for( j = 0; j < 3 ; j++){
            if(i == j) {
                matrix [i][j] = 1.0;
            }else {
                matrix[i][j] = 0.0;
            }
        }
    
    }
}

void scalar_multiply(float matrix[3][3], float scalar){
    int i;
    int j;

        for(i = 0; i < 3; i++){
            for (j = 0; j< 3; j++){
                matrix[i][j] *= scalar;
            }
        }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]){
    int i;
    int j;

    for ( i = 0; i < 3; i++){
        for( j = 0; j < 3; j++){
            c[i][j] = 0.0;
            for(int k = 0; k < 3; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}



Point transform_point(const float matrix[3][3], const Point point) {
    float result[3] = {0.0, 0.0, 1.0};

    result[0] = matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2] * point.w;
    result[1] = matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2] * point.w;
    result[2] = matrix[2][0] * point.x + matrix[2][1] * point.y + matrix[2][2] * point.w;

    return (Point){result[0] / result[2], result[1] / result[2], 1.0f};
}

void scale(float matrix[3][3], float scale_factor){
    int i;
    int j;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            matrix[i][j] *= scale_factor;
        }
    }
}

void shift(float matrix[3][3], float x_shift, float y_shift) {
    matrix[0][2] += x_shift;
    matrix[1][2] += y_shift;
}

void rotate(float matrix[3][3], float angle_in_degrees) {
    float angle_in_radians = angle_in_degrees * PI / 180.0;
    float cos_angle = cos(angle_in_radians);
    float sin_angle = sin(angle_in_radians);

    float temp[3][3] = {
        {cos_angle, -sin_angle, 0.0},
        {sin_angle, cos_angle, 0.0},
        {0.0, 0.0, 1.0}
    };

    float result[3][3];
    multiply_matrices(matrix, temp, result);

    // Copy result back to matrix
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = result[i][j];
        }
    }
}




