#ifndef CUDA_VECTOR2D_CUH
#define CUDA_VECTOR2D_CUH

#include <cmath>

#include "body.h"


/**
 * @brief u = (0, 0)
 */
__device__
void v2d_reset(vector2d* u);

/**
 * @brief Copy a vector into another
 * 
 * @param v2dp Pointer to where the copy will be stored
 * @param v2dc Pointer to the vector to copy
 */ 
__device__
void v2d_copy(vector2d* v2dp, vector2d* v2dc);

/**
 * @brief u = u+v
 * 
 */
__device__
void v2d_incr(vector2d* u, vector2d* v);

/**
 * @brief w = u + v
 */
__device__
void v2d_add(vector2d* u, vector2d * v, vector2d* w);

/**
 * @brief u = u - v
 * 
 * @param u 
 * @param v 
 */
__device__
void v2d_decr(vector2d* u, vector2d* v);
/**
 * @brief w = u - v
 */
__device__
void v2d_sub(vector2d* u, vector2d* v, vector2d* w);

/**
 * @brief u = k * u
 * 
 * @param k 
 * @param u 
 */
__device__
void v2d_scale(double k, vector2d* u);

/**
 * @brief u = u / norm(u)
 * 
 * @param u 
 */
__device__
void v2d_normalise(vector2d* u);

/**
 * @param u 
 * @return the squared norm of u 
 */
__device__
double v2d_norm2(vector2d* u);
/**
 * @param u 
 * @return the norm of u 
 */
__device__
double v2d_norm(vector2d* u);

#endif