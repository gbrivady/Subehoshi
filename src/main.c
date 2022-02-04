#include <stdio.h>
#include "main.h"
#include <time.h>
#define SDL_MAIN_HANDLED

#include <SDL.h>
//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main(int argc, char *argv[]){
    
    body* body_list[100];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            body_list[10*i+j] = create_body(100. * i - 450, 100. * j - 450, 0.0, 0.0, 1.0);
        }
        
    }
    
    // body* body1 = create_body(50.0, 0.0, 0.0, 0.05, 1.0);
    // body* body2 = create_body(-50.0, 0.0, 0.0, -0.05, 1.0);
    // body* body3 = create_body(0.0, 500.0, -0.03, 0.0, 1.0);
    // body* body4 = create_body(0.0, -500.0, 0.03, 0.0, 1.0);

    // body* body_list[4] = {body1, body2, body3, body4};
    vector2d*** k_1234 = init_k(100);

    // printf("Object one : v1 = (%lf, %lf) u1 = (%lf, %lf) \n", body1->vel->x, body1->vel->y, body1->pos->x, body1->pos->y);
    // printf("Object two : v2 = (%lf, %lf) u2 = (%lf, %lf) \n", body2->vel->x, body2->vel->y, body2->pos->x, body2->pos->y);
    // printf("Object thr : v3 = (%lf, %lf) u3 = (%lf, %lf) \n", body3->vel->x, body3->vel->y, body3->pos->x, body3->pos->y);
    // printf("Object fou : v4 = (%lf, %lf) u4 = (%lf, %lf) \n", body4->vel->x, body4->vel->y, body4->pos->x, body4->pos->y);

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }else{
        window = SDL_CreateWindow( "Subehoshi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            exit(1);
        }
    }
    int run = 1;
    SDL_Event event;
    SDL_FRect rects[100];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int ind = 10*i+j;
            SDL_FRect rect = {body_list[ind]->pos->x, body_list[ind]->pos->y, 5., 5.};
            rects[ind] = rect;
        }
        
    }
    // SDL_FRect rect1 = {body1->pos->x, body1->pos->y, 5., 5.};
    // SDL_FRect rect2 = {body2->pos->x, body2->pos->y, 5., 5.};
    // SDL_FRect rect4 = {body4->pos->x, body4->pos->y, 5., 5.};
    // SDL_FRect rect3 = {body3->pos->x, body3->pos->y, 5., 5.};
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        exit(1);
    }
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    // SDL_FRect rects[4] = {rect1, rect2, rect3, rect4};
    int paused = 1;
    while (paused)
    {
        while( SDL_PollEvent( &event ) )
        {
            if (event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_p){
                    paused = 0;
                }
            }
        } 
    }
    
    while(run)
    {
        for(int i = 0; i < 1; i++){
            update(body_list, 100, 1, k_1234);
        }
        // printf("gravity OK \n");
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                int ind = 10*i+j;
                rects[ind].x = body_list[ind]->pos->x+SCREEN_WIDTH/2.0;
                rects[ind].y = body_list[ind]->pos->y+SCREEN_HEIGHT/2.0;
            }
        
        }
        // rect1.x = body1->pos->x+SCREEN_WIDTH/2.0;
        // rect1.y = body1->pos->y+SCREEN_HEIGHT/2.0;
        // rect2.x = body2->pos->x+SCREEN_WIDTH/2.0;
        // rect2.y = body2->pos->y+SCREEN_HEIGHT/2.0;
        // rect3.x = body3->pos->x+SCREEN_WIDTH/2.0;
        // rect3.y = body3->pos->y+SCREEN_HEIGHT/2.0;
        // rect4.x = body4->pos->x+SCREEN_WIDTH/2.0;
        // rect4.y = body4->pos->y+SCREEN_HEIGHT/2.0;

        SDL_RenderFillRectsF(renderer, rects, 100);
        SDL_RenderPresent(renderer);

        // printf("Object one : v1 = (%lf, %lf) u1 = (%lf, %lf) \n", body1->vel->x, body1->vel->y, body1->pos->x, body1->pos->y);
        // printf("Object two : v2 = (%lf, %lf) u2 = (%lf, %lf) \n", body2->vel->x, body2->vel->y, body2->pos->x, body2->pos->y);
        // printf("Object thr : v3 = (%lf, %lf) u3 = (%lf, %lf) \n", body3->vel->x, body3->vel->y, body3->pos->x, body3->pos->y);
        // printf("Object fou : v4 = (%lf, %lf) u4 = (%lf, %lf) \n", body4->vel->x, body4->vel->y, body4->pos->x, body4->pos->y);
        while( SDL_PollEvent( &event ) )
        {
            if (event.type == SDL_QUIT)
            {
                run = 0;
            }
        } 
    }
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow( window );
    SDL_Quit();
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
