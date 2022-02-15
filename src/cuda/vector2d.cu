#include "vector2d.cuh"

__device__
void v2d_reset(vector2d* u){
    u->x = 0;
    u->y = 0;
}

__device__
void v2d_copy(vector2d* v2dp, vector2d* v2dc){
    v2dp->x = v2dc->x;
    v2dp->y = v2dc->y;
}

__device__
void v2d_incr(vector2d* u, vector2d* v){
    u->x = u->x + v->x;
    u->y = u->y + v->y;
}

__device__
void v2d_add(vector2d * u, vector2d * v, vector2d* w){
    w->x = u->x + v->x;
    w->y = u->y + v->y;
}

__device__
void v2d_decr(vector2d* u, vector2d* v){
    u->x = u->x - v->x;
    u->y = u->y - v->y;
}

__device__
void v2d_sub(vector2d * u, vector2d * v, vector2d* w){
    w->x = u->x - v->x;
    w->y = u->y - v->y;
}

__device__
void v2d_scale(double k, vector2d* u){
    u->x = k*u->x;
    u->y = k*u->y;
}

__device__
void v2d_normalise(vector2d* u){
    double norm = v2d_norm(u);
    u->x = u->x/norm;
    u->y = u->y/norm;
}

__device__
double v2d_norm2(vector2d* u){
    return u->x*u->x + u->y*u->y;
}
__device__
double v2d_norm(vector2d* u){
    double norm = u->x*u->x + u->y*u->y;
    return sqrt(norm);
}
