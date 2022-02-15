/**
 * @file body.h
 * @author Grégory Brivady (gregory.brivady@gmail.com)
 * @brief 
 * @version 0.2
 * @date 2022-02-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BODY_H
#define BODY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
//#include "vector2d.h"

typedef struct vector2Ddouble
{
    double x;
    double y;
} vector2d;

typedef struct body
{
    double mass;
    vector2d pos;
    vector2d vel;

}body;

body* create_body(double x, double y, double vx, double vy, double mass);

void free_body(body* body);

#ifdef __cplusplus
}
#endif
#endif