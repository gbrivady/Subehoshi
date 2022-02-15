#ifndef CUDA_UPDATE_H
#define CUDA_UPDATE_H

#include "body.h"
#include "vector2d.cuh"


#define CU_MINIMAL_DISTANCE_SQ 25.0

__device__
void cu_calc_acc(body* body1, body* body2, vector2d* output_v2d, vector2d* pos_offset);

__global__
void cu_calc_k1k2(body* body_list, const int nb_body, const double timestep,
vector2d* k1, vector2d* k2);

__global__
void cu_calc_k3k4(body* body_list, const int nb_body, const double timestep,
vector2d* k1, vector2d* k2, vector2d* k3, vector2d* k4);

__global__ 
void cu_update(body* body_list, const int nb_body, const double timestep,
vector2d* k1, vector2d* k2, vector2d* k3, vector2d* k4);

__global__
void cu_reset_k(vector2d* k1, vector2d* k2, vector2d* k3, vector2d* k4, const int nb_body);

#endif