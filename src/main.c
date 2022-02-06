#include <stdio.h>
#include "main.h"
#include <time.h>
#include <stdlib.h>
//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main(int argc, char *argv[]){
    body* body_list[100];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            srand(time(NULL));
            body_list[10*i+j] = create_body(100. * i, 100. * j, 0, 0, 1.0);
        }
        
    }
    vector2d*** k_1234 = init_k(100);
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    start_graphics(SCREEN_WIDTH, SCREEN_HEIGHT, window, &renderer);
    SDL_Event event;
    SDL_FRect rects[100];
    init_frames(body_list, 100, rects);
    enum keyboard_action cur_action;
    draw_frame(body_list, 100, renderer, rects);
    int paused = 1;
    int running = 1;
    while(running){
        cur_action = check_keyboard();
        switch (cur_action){
        case EXIT_SIM:
            running = 0;
            end_graphics(window, &renderer);
            break;
        case TOGGLE_SIM:
            paused = !paused;
            break;
        case NEXT_FRAME:
            if (paused){
                for(int i = 0; i < 2; i++){
                    update(body_list, 100, 1, k_1234);
                }
                draw_frame(body_list, 100, renderer, rects);
            }
            break;
        default:
            break;
        }
        if(!paused){
            for(int i = 0; i < 2; i++){
                update(body_list, 100, 1, k_1234);
            }
            draw_frame(body_list, 100, renderer, rects);
        }
    }

    free_k(k_1234, 100);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            free_body(body_list[10*i+j]);
        }
        
    }
    
    // free_body(body1);
    // free_body(body2);
    // free_body(body3);
    // free_body(body4);


}
