/**
 * @file body.h
 * @author Grégory Brivady (gregory.brivady@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BODY_H
#define BODY_H

#include "vector2d.h"

typedef struct body
{
    vector2d* vel;
    vector2d* pos;
    double mass;

}body;

body* create_body(double x, double y, double vx, double vy, double mass);

void free_body(body* body);
#endif