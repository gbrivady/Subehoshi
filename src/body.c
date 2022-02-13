#include "body.h"

body* create_body(double x, double y, double vx, double vy, double mass){
    body* p_b = malloc(sizeof(body));
    if (p_b == NULL)
    {
        // TODO : pretty error message
        exit(1);
    
    }
    p_b->mass = mass;
    p_b->pos.x = x;
    p_b->pos.y = y;
    p_b->vel.x = vx;
    p_b->vel.y = vy;
    return p_b;
}

void free_body(body* body){
    free(body);
}
