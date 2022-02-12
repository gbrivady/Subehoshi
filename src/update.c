#include "update.h"

vector2d*** init_k(const int nb_body){
    vector2d*** k_1234 = malloc(4*sizeof(vector2d**));
    vector2d** k1 = malloc(nb_body*sizeof(vector2d*));
    vector2d** k2 = malloc(nb_body*sizeof(vector2d*));
    vector2d** k3 = malloc(nb_body*sizeof(vector2d*));
    vector2d** k4 = malloc(nb_body*sizeof(vector2d*));
    if (k_1234 == NULL || k1 == NULL || k2 == NULL || k3 == NULL || k4 == NULL)
    {
        // TODO : pretty error message
        exit(1);
    }
    k_1234[0] = k1;
    k_1234[1] = k2;
    k_1234[2] = k3;
    k_1234[3] = k4;
    for (int i = 0; i < nb_body; i++)
    {
        k1[i] = v2d_null();
        k2[i] = v2d_null();
        k3[i] = v2d_null();
        k4[i] = v2d_null();
    }
    return k_1234;
}

void free_k(vector2d*** k_1234, const int nb_body){
    for (int i = 0; i < nb_body; i++)
    {
        free(k_1234[0][i]);
        free(k_1234[1][i]);
        free(k_1234[2][i]);
        free(k_1234[3][i]);
    }
    free(k_1234[0]);
    free(k_1234[1]);
    free(k_1234[2]);
    free(k_1234[3]);
    free(k_1234);
}

void calc_acc(vector2d* pos1, vector2d* pos2, vector2d* output_v2d){
    v2d_sub(pos2, pos1, output_v2d);
    double strength = pow(fmax(v2d_norm2(output_v2d), MINIMAL_DISTANCE_SQ), -3.0/2.0);    
    v2d_scale(strength, output_v2d);
}

void calc_k1(body** body_list, const int nb_body, vector2d** k1){
    //first iteration : kill the old acc
    k1[0]->x = 0;
    k1[0]->y = 0;
    vector2d* temp_acc = v2d_null();
    for (int i = 1; i < nb_body; i++)
    {
        k1[i]->x = 0;
        k1[i]->y = 0;
        calc_acc(body_list[0]->pos, body_list[i]->pos, temp_acc);
        v2d_incr(k1[0], temp_acc);
        v2d_scale(-1.0, temp_acc);
        v2d_incr(k1[i], temp_acc);
    }
    for (int i = 1; i < nb_body-1; i++)
    {
        for (int j = i+1; j < nb_body; j++)
        {
            calc_acc(body_list[i]->pos, body_list[j]->pos, temp_acc);
            v2d_incr(k1[i], temp_acc);
            v2d_scale(-1.0, temp_acc);
            v2d_incr(k1[j], temp_acc);
        }
    }
    free(temp_acc);
}

void calc_k234(body** body_list, const int nb_body, const double timestep, 
            vector2d** k1, vector2d** k2, vector2d** k3, vector2d** k4){
    //
    v2d_reset(k2[0]);
    v2d_reset(k3[0]);
    v2d_reset(k4[0]);
    vector2d* temp_acc = v2d_null();
    vector2d* temp_pos_k = v2d_null();
    vector2d* temp_v2d = v2d_null();

    v2d_copy(temp_pos_k, body_list[0]->pos);

    //k2 is calculated with pos + h*vel/2
    v2d_copy(temp_v2d, body_list[0]->vel);
    v2d_scale(timestep/2.0, temp_v2d);
    v2d_incr(temp_pos_k, temp_v2d);

    //Calculates k2
    for (int i = 1; i < nb_body; i++)
    {
        v2d_reset(k2[i]);
        v2d_reset(k4[i]);
        calc_acc(temp_pos_k, body_list[i]->pos, temp_acc);
        v2d_incr(k2[0], temp_acc);
    }
    //Calculates k3
    v2d_copy(temp_v2d, k1[0]);
    v2d_scale(timestep*timestep/4.0, temp_v2d);
    v2d_incr(temp_pos_k, temp_v2d);

    for (int i = 1; i < nb_body; i++)
    {
        v2d_reset(k3[i]);
        calc_acc(temp_pos_k, body_list[i]->pos, temp_acc);
        v2d_incr(k2[0], temp_acc);
    }

    for (int i = 1; i < nb_body; i++)
    {
        v2d_copy(temp_pos_k, body_list[i]->pos);
        v2d_copy(temp_v2d, body_list[i]->vel);
        v2d_scale(timestep/2.0, temp_v2d);
        v2d_incr(temp_pos_k, temp_v2d);
        for (int j = 0; j < nb_body; j++)
        {
            if(i == j)
                continue;
            calc_acc(temp_pos_k, body_list[j]->pos, temp_acc);
            v2d_incr(k2[i], temp_acc);
        }
        v2d_copy(temp_v2d, k1[i]);
        v2d_scale(timestep*timestep/4.0, temp_v2d);
        v2d_incr(temp_pos_k, temp_v2d);
        for (int j = 0; j < nb_body; j++)
        {
            if(i == j)
                continue;
            calc_acc(temp_pos_k, body_list[j]->pos, temp_acc);
            v2d_incr(k3[i], temp_acc);
        }
    }

    //Calculates k4
    for (int i = 0; i < nb_body; i++)
    {
        //temp_pos = old_pos + h*vel + ...
        v2d_copy(temp_pos_k, body_list[i]->pos);
        v2d_copy(temp_v2d, body_list[i]->vel);
        v2d_scale(timestep, temp_v2d);
        v2d_incr(temp_pos_k, temp_v2d);

        // ... timestep**2 * k2 / 2
        v2d_copy(temp_v2d, k2[i]);
        v2d_scale(timestep*timestep/2, temp_v2d);
        v2d_incr(temp_pos_k, temp_v2d);
        for (int j = 0; j < nb_body; j++)
        {
            if (i == j)
                continue;
            calc_acc(temp_pos_k, body_list[j]->pos, temp_acc);
            v2d_incr(k4[i], temp_acc);
        }
        
    }
    free(temp_acc);
    free(temp_pos_k);
    free(temp_v2d);
}

void update(body** body_list, const int nb_body, const double timestep, vector2d*** k_1234){
    calc_k1(body_list, nb_body, k_1234[0]);
    calc_k234(body_list, nb_body, timestep, k_1234[0], k_1234[1], k_1234[2], k_1234[3]);

    vector2d* temp_v2d = v2d_null();
    //pos = old_pos + timestep*old_vel + timestep**2 * (k1 + k2 + k3)/6
    //vel = old_vel + timestep * (k1 + 2*k2 + 2*k3 + k4)/6
    for (int i = 0; i < nb_body; i++)
    {
        v2d_copy(temp_v2d, body_list[i]->vel);
        v2d_scale(timestep, temp_v2d);
        v2d_incr(body_list[i]->pos, temp_v2d);

        v2d_copy(temp_v2d, k_1234[0][i]);
        v2d_incr(temp_v2d, k_1234[1][i]);
        v2d_incr(temp_v2d, k_1234[2][i]);
        v2d_scale(timestep*timestep/6.0, temp_v2d);
        v2d_incr(body_list[i]->pos, temp_v2d);

        v2d_copy(temp_v2d, k_1234[1][i]);
        v2d_incr(temp_v2d, k_1234[2][i]);
        v2d_scale(2, temp_v2d);

        v2d_incr(temp_v2d, k_1234[0][i]);
        v2d_incr(temp_v2d, k_1234[3][i]);
        v2d_scale(timestep/6.0, temp_v2d);
        v2d_incr(body_list[i]->vel, temp_v2d);

    }
    free(temp_v2d);
}
