#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <math.h>

// Point struktúra definiálása
typedef struct {
    float x, y, w;
} Point;

// Mátrix inicializálása nullákkal
void init_zero_matrix(float matrix[3][3]);

// Mátrix kiíratása
void print_matrix(const float matrix[3][3]);

// Mátrixok összeadása
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

// Egységmátrix inicializálása
void init_identity_matrix(float matrix[3][3]);

// Mátrix szorzása skalárral
void scalar_multiply(float matrix[3][3], float scalar);

// Mátrixok szorzása
void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

// Pont transzformálása mátrixszal
Point transform_point(const float matrix[3][3], const Point point);

// Méretezési transzformáció
void scale(float matrix[3][3], float scale_factor);

// Eltolási transzformáció
void shift(float matrix[3][3], float x_shift, float y_shift);

// Forgató transzformáció
void rotate(float matrix[3][3], float angle_in_degrees);

#endif // MATRIX_H