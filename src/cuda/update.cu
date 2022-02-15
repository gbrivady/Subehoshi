#include "update.cuh"

__device__
void cu_calc_acc(body* body1, body* body2, vector2d* output_v2d, vector2d* pos_offset){
    v2d_add(&(body1->pos), pos_offset, output_v2d);
    v2d_sub(&(body2->pos), output_v2d, output_v2d);
    double strength = body1->mass * body2->mass *
    pow(fmax(v2d_norm2(output_v2d), CU_MINIMAL_DISTANCE_SQ), -3.0/2.0);    
    v2d_scale(strength, output_v2d);
}

__global__
void cu_calc_k1k2(body* body_list, const int nb_body, const double timestep,
vector2d* k1, vector2d* k2){

    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if(i >= nb_body || j >= nb_body || i == j)
        return;

    vector2d pos_offset = {0., 0.};
    vector2d temp_k = {0., 0.};
    cu_calc_acc(&body_list[i], &body_list[j], &temp_k, &pos_offset);

    atomicAdd(&(k1[i].x), temp_k.x);
    atomicAdd(&(k1[i].y), temp_k.y);

    pos_offset.x = (body_list[i].vel.x) * timestep / 2. ;
    pos_offset.y = (body_list[i].vel.y) * timestep / 2. ;

    cu_calc_acc(&body_list[i], &body_list[j], &temp_k, &pos_offset);

    atomicAdd(&(k2[i].x), temp_k.x);
    atomicAdd(&(k2[i].y), temp_k.y);
}

__global__ 
void cu_calc_k3k4(body* body_list, const int nb_body, const double timestep,
vector2d* k1, vector2d* k2, vector2d* k3, vector2d* k4){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if(i >= nb_body || j >= nb_body)
        return;

    vector2d pos_offset = {0., 0.};
    vector2d temp_k = {0., 0.};

    pos_offset.x = (body_list[i].vel.x) * timestep / 2. ;
    pos_offset.y = (body_list[i].vel.y) * timestep / 2. ;

    pos_offset.x += (k1[i].x) * (timestep*timestep) / 4. ;
    pos_offset.y += (k1[i].y) * (timestep*timestep) / 4. ;

    cu_calc_acc(&body_list[i], &body_list[j], &temp_k, &pos_offset);

    atomicAdd(&(k3[i].x), temp_k.x);
    atomicAdd(&(k3[i].y), temp_k.y);

    pos_offset.x = (body_list[i].vel.x) * timestep;
    pos_offset.y = (body_list[i].vel.y) * timestep;

    pos_offset.x += (k2[i].x) * (timestep*timestep) / 2. ;
    pos_offset.y += (k2[i].y) * (timestep*timestep) / 2. ;

    cu_calc_acc(&body_list[i], &body_list[j], &temp_k, &pos_offset);

    atomicAdd(&(k4[i].x), temp_k.x);
    atomicAdd(&(k4[i].y), temp_k.y);
}

__global__ 
void cu_update(body* body_list, const int nb_body, const double timestep,
vector2d* k1, vector2d* k2, vector2d* k3, vector2d* k4){
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if(i >= nb_body)
        return;

    vector2d temp_v2d;

    v2d_copy(&temp_v2d, &(body_list[i].vel));
    v2d_scale(timestep, &temp_v2d);
    v2d_incr(&(body_list[i].pos), &temp_v2d);

    v2d_copy(&temp_v2d, &k1[i]);
    v2d_incr(&temp_v2d, &k2[i]);
    v2d_incr(&temp_v2d, &k3[i]);
    v2d_scale(timestep*timestep/6.0, &temp_v2d);
    v2d_incr(&(body_list[i].pos), &temp_v2d);

    v2d_copy(&temp_v2d, &k2[i]);
    v2d_incr(&temp_v2d, &k3[i]);
    v2d_scale(2, &temp_v2d);

    v2d_incr(&temp_v2d, &k1[i]);
    v2d_incr(&temp_v2d, &k4[i]);
    v2d_scale(timestep/6.0, &temp_v2d);
    v2d_incr(&(body_list[i].vel), &temp_v2d);
    
}

__global__
void cu_reset_k(vector2d* k1, vector2d* k2, vector2d* k3, vector2d* k4, const int nb_body){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i >= nb_body)
        return;
    k1[i].x = 0;
    k1[i].y = 0;
    k2[i].x = 0;
    k2[i].y = 0;
    k3[i].x = 0;
    k3[i].y = 0;
    k4[i].x = 0;
    k4[i].y = 0;
}
