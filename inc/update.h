/**
 * @file update.h
 * @author Grégory Brivady (gregory.brivady@gmail.com)
 * @brief 
 * @version 0.2
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UPDATE_H
#define UPDATE_H

#include "vector2d.h"
#include "body.h"

#define MINIMAL_DISTANCE_SQ 25.0

vector2d*** init_k(const int nb_body);

void free_k(vector2d*** k_1234, const int nb_body);

void calc_k1(body** body_list, const int nb_body, vector2d** k1);

void calc_k234(body** body_list, const int nb_body, const double timestep, 
               vector2d** k1, vector2d** k2, vector2d** k3, vector2d** k4);

void calc_acc(vector2d* pos1, vector2d* pos2, vector2d* output);

void update(body** body_list, const int nb_body, const double timestep, vector2d*** k_1234);

#endif