#include "vector2d.h"

vector2d *v2d_null(){
    vector2d* p_u = malloc(sizeof(vector2d));
    if (p_u == NULL)
    {
        // TODO : pretty error message
        exit(1);
    }
    return p_u;
}

void v2d_copy(vector2d* v2dp, vector2d* v2dc){
    v2dp->x = v2dc->x;
    v2dp->y = v2dc->y;
}

vector2d* v2d_copy_f(vector2d *v2d){
    vector2d* v2d_ = v2d_null();
    v2d_copy(v2d_, v2d);
    return v2d_;
}

void v2d_add(vector2d* u, vector2d* v){
    u->x = u->x + v->x;
    u->y = u->y + v->y;
}

vector2d *v2d_add_f(vector2d * u, vector2d * v){
    vector2d* w = v2d_null();
    w->x = u->x + v->x;
    w->y = u->y + v->y;
    return w;
}

void v2d_sub(vector2d* u, vector2d* v){
    u->x = u->x - v->x;
    u->y = u->y - v->y;
}
vector2d *v2d_sub_f(vector2d * u, vector2d * v){
    vector2d* w = v2d_null();
    w->x = u->x - v->x;
    w->y = u->y - v->y;
    return w;
}

void v2d_scale(double k, vector2d* u){
    u->x = k*u->x;
    u->y = k*u->y;
}
vector2d *v2d_scale_f(double k, vector2d *u){
    vector2d* v = v2d_copy_f(u);
    v2d_scale(k, v);
    return v;\
}

void v2d_normalise(vector2d* u){
    double norm = v2d_norm(u);
    u->x = u->x/norm;
    u->y = u->y/norm;
}
vector2d *v2d_normalise_f(vector2d * u){
    vector2d* v = v2d_copy_f(u);
    v2d_scale(1/v2d_norm(v), v);
    return v;
}


double v2d_norm2(vector2d* u){
    return u->x*u->x + u->y*u->y;
}
double v2d_norm(vector2d* u){
    double norm = u->x*u->x + u->y*u->y;
    return sqrt(norm);
}
