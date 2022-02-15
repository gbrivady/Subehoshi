#include <stdlib.h>
#include <time.h>
#include "update.cuh"
#include "vector2d.cuh"
#include "display_cu.h"
#include "body.h"

//Screen dimensions
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main(int argc, char const *argv[])
{
    int nb_body = 900;
    dim3 grid_th(32, 32);
    //dim3 grid_blk(__max(1, nb_body/16),__max(1, nb_body/16));
    dim3 grid_blk(1 + nb_body/32, 1 + nb_body/32);
    /* Setup for timing */
    struct timespec phX_time_start;
    struct timespec phX_time_end;
    unsigned long long avr_phX_time = 0;
    unsigned int phX_frame_nb = 0;

    /* Setup for PhX */
    body* body_list = (body*) malloc(nb_body*sizeof(body));
    for(int i = 0; i < nb_body; i++){
        body_list[i].pos.x = 33 * (i % 30);
        body_list[i].pos.y = 33 * (i / 30);
        body_list[i].vel.x = 0;
        body_list[i].vel.y = 0;
        body_list[i].mass = 1;
    }

    body* body_list_gpu;
    cudaMalloc(&body_list_gpu, nb_body*sizeof(body));
    cudaMemcpy(body_list_gpu, body_list, nb_body*sizeof(body), cudaMemcpyHostToDevice);
    
    vector2d* k1;
    vector2d* k2;
    vector2d* k3;
    vector2d* k4;
    cudaMalloc(&k1, nb_body * sizeof(vector2d));
    cudaMalloc(&k2, nb_body * sizeof(vector2d));
    cudaMalloc(&k3, nb_body * sizeof(vector2d));
    cudaMalloc(&k4, nb_body * sizeof(vector2d));

    /* Setup graphics */
    int paused = 1;
    int running = 1;
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    enum keyboard_action cur_action;
    SDL_Event event;
    SDL_FRect* rects =(SDL_FRect*) malloc(nb_body*sizeof(SDL_FRect));
    start_graphics(SCREEN_WIDTH, SCREEN_HEIGHT, window, &renderer);
    init_frames(body_list, nb_body, rects);
    draw_frame(body_list, nb_body, renderer, rects);

    /* Graphics main loop */
    while(running){
        cur_action = check_keyboard();
        switch (cur_action){
        case EXIT_SIM:
            running = 0;
            end_graphics(window);
            break;
        case TOGGLE_SIM:
            paused = !paused;
            break;
        case NEXT_FRAME:
            if (paused){
                timespec_get(&phX_time_start, TIME_UTC);
                for(int i = 0; i < 2; i++){
                    /* START OF PHYSIC ITERATION */
                    cu_reset_k<<<1 + nb_body/256, 256>>>(k1, k2, k3, k4, nb_body);
                    cudaDeviceSynchronize();
                    cu_calc_k1k2<<<grid_blk, grid_th>>>(body_list_gpu, nb_body, 1., k1, k2);
                    cudaDeviceSynchronize();
                    cu_calc_k3k4<<<grid_blk, grid_th>>>(body_list_gpu, nb_body, 1., k1, k2, k3, k4);
                    cudaDeviceSynchronize();
                    cu_update<<<1 + nb_body/256, 256>>>(body_list_gpu, nb_body, 1., k1, k2, k3, k4);
                    cudaDeviceSynchronize();
                    cudaMemcpy(body_list, body_list_gpu, nb_body*sizeof(body), cudaMemcpyDeviceToHost);
                    /* END OF PHYSIC ITERATION */                
                }
                timespec_get(&phX_time_end, TIME_UTC);
                draw_frame(body_list, nb_body, renderer, rects);
                phX_frame_nb+= 1;
                avr_phX_time += (phX_time_end.tv_sec - phX_time_start.tv_sec)*1000000000 + phX_time_end.tv_nsec-phX_time_start.tv_nsec;
            }
            break;
        default:
            break;
        }
        if(!paused){
            timespec_get(&phX_time_start, TIME_UTC);
            for(int i = 0; i < 2; i++){
                /* START OF PHYSIC ITERATION */
                cu_reset_k<<<1 + nb_body/256, 256>>>(k1, k2, k3, k4, nb_body);
                cudaDeviceSynchronize();
                cu_calc_k1k2<<<grid_blk, grid_th>>>(body_list_gpu, nb_body, 1., k1, k2);
                cudaDeviceSynchronize();
                cu_calc_k3k4<<<grid_blk, grid_th>>>(body_list_gpu, nb_body, 1., k1, k2, k3, k4);
                cudaDeviceSynchronize();
                cu_update<<<1 + nb_body/256, 256>>>(body_list_gpu, nb_body, 1., k1, k2, k3, k4);
                cudaDeviceSynchronize();
                cudaMemcpy(body_list, body_list_gpu, nb_body*sizeof(body), cudaMemcpyDeviceToHost);
                /* END OF PHYSIC ITERATION */                     
            }
            timespec_get(&phX_time_end, TIME_UTC);
            phX_frame_nb += 1;
            avr_phX_time += (phX_time_end.tv_sec - phX_time_start.tv_sec)*1000000000 + phX_time_end.tv_nsec-phX_time_start.tv_nsec;
            draw_frame(body_list, nb_body, renderer, rects);
        }
    }

    // /* START OF PHYSIC ITERATION */
    // cu_reset_k<<<__max(1, nb_body/256), 256>>>(k1, k2, k3, k4, nb_body);
    // cudaDeviceSynchronize();
    // cu_calc_k1k2<<<grid_blk, grid_th>>>(body_list_gpu, nb_body, 1., k1, k2);
    // cudaDeviceSynchronize();
    // cu_calc_k3k4<<<grid_blk, grid_th>>>(body_list_gpu, nb_body, 1., k1, k2, k3, k4);
    // cudaDeviceSynchronize();
    // cu_update<<<__max(1, nb_body/256), 256>>>(body_list_gpu, nb_body, 1., k1, k2, k3, k4);
    // cudaDeviceSynchronize();
    // cudaMemcpy(body_list, body_list_gpu, nb_body*sizeof(body), cudaMemcpyDeviceToHost);
    // /* END OF PHYSIC ITERATION */
    printf("Average frame duration : %lld microseconds over %d frames \n", (avr_phX_time/phX_frame_nb)/1000 , phX_frame_nb);

    cudaFree(k1);
    cudaFree(k2);
    cudaFree(k3);
    cudaFree(k4);
    cudaFree(body_list_gpu);
    free(body_list);

    return 0;
}
