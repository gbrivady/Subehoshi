#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"
//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main(int argc, char *argv[]){
    struct timespec phX_time_start;
    struct timespec phX_time_end;
    unsigned long long avr_phX_time = 0;
    unsigned int phX_frame_nb = 0;
    int nb_body = 900;

    body** body_list = malloc(nb_body*sizeof(body*));
    for (int i = 0; i < nb_body; i++)
    {
        body_list[i] = create_body(33 * (i % 30), 33 * (i / 30), 0, 0, 1.0);        
    }
    vector2d*** k_1234 = init_k(nb_body);
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    start_graphics(SCREEN_WIDTH, SCREEN_HEIGHT, window, &renderer);
    SDL_Event event;
    SDL_FRect* rects =(SDL_FRect*) malloc(nb_body*sizeof(SDL_FRect));
    init_frames(body_list, nb_body, rects);
    enum keyboard_action cur_action;
    draw_frame(body_list, nb_body, renderer, rects);
    int paused = 1;
    int running = 1;
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
                    update(body_list, nb_body, 1, k_1234);
                }
                timespec_get(&phX_time_end, TIME_UTC);
                draw_frame(body_list, nb_body, renderer, rects);
                //printf("PhX time : %ld ns \n", phX_time_end.tv_nsec-phX_time_start.tv_nsec);
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
                update(body_list, nb_body, 1, k_1234);
            }
            timespec_get(&phX_time_end, TIME_UTC);
            //printf("PhX time : %ld ns \n", phX_time_end.tv_nsec-phX_time_start.tv_nsec);
            phX_frame_nb += 1;
            avr_phX_time += (phX_time_end.tv_sec - phX_time_start.tv_sec)*1000000000 + phX_time_end.tv_nsec-phX_time_start.tv_nsec;
            draw_frame(body_list, nb_body, renderer, rects);
        }
    }

    free_k(k_1234, nb_body);
    for (int i = 0; i < nb_body; i++)
    {
        free_body(body_list[nb_body]);
    }
    printf("Average frame duration : %lld microseconds over %d frames \n", (avr_phX_time/phX_frame_nb)/1000 , phX_frame_nb);
    // free_body(body1);
    // free_body(body2);
    // free_body(body3);
    // free_body(body4);

    return 0;
}
