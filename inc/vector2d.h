/**
 * @file vector2d.h
 * @author Gregory Brivady (gregory.brivady@gmail.com)
 * @brief Simple definition of a two-dimensionnal double vector.
 * @version 0.1
 * @date 2022-01-30
 * 
 * @copyright Copyright (c) 2022
 * 
 * @details Each function is provided with two version : a functionnal version that
 *  returns a pointer to the new vector, that need to be freed, and an imperative 
 *  version that modifies the vector passed as the first argument. The function 
 *  returning the null vector is the only exception. Functionnal versions of the 
 *  functions are named with the following convention : ImperativeFunctionName_f
 */

#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <math.h>
#include <stdlib.h>

/**
 * @brief A 2D double vector.
 * 
 */
typedef struct vector2Ddouble
{
    double x;
    double y;
} vector2d;

/**
 * @return A pointer to the vector (0, 0).
 */
vector2d *v2d_null();

/**
 * @brief Copy a vector into another
 * 
 * @param v2dp Pointer to where the copy will be stored
 * @param v2dc Pointer to the vector to copy
 */
void v2d_copy(vector2d* v2dp, vector2d* v2dc);

/**
 * @param v2d vector to copy
 * @return a copy of the vector 
 */
vector2d *v2d_copy_f(vector2d *v2d);

/**
 * @brief u = u+v
 * 
 */
void v2d_add(vector2d* u, vector2d* v);
vector2d *v2d_add_f(vector2d *, vector2d *);

/**
 * @brief u = u - v
 * 
 * @param u 
 * @param v 
 */
void v2d_sub(vector2d* u, vector2d* v);
vector2d *v2d_sub_f(vector2d *, vector2d *);

/**
 * @brief u = k * u
 * 
 * @param k 
 * @param u 
 */
void v2d_scale(double k, vector2d* u);
vector2d *v2d_scale_f(double, vector2d *);

/**
 * @brief u = u / norm(u)
 * 
 * @param u 
 */
void v2d_normalise(vector2d* u);
vector2d *v2d_normalise_f(vector2d *);

/**
 * @param u 
 * @return the squared norm of u 
 */
double v2d_norm2(vector2d* u);
/**
 * @param u 
 * @return the norm of u 
 */
double v2d_norm(vector2d* u);

#endif