#include "display_cu.h"


void start_graphics(int width, int height, SDL_Window* window, SDL_Renderer** p_renderer){

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }else{
        window = SDL_CreateWindow( "Subehoshi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            exit(1);
        }
    }
    *p_renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(*p_renderer == NULL){
        exit(1);
    }
}

void end_graphics(SDL_Window* window){
    SDL_DestroyWindow( window );
    SDL_Quit();
}


void init_frames(body* body_list, int nb_body, SDL_FRect* rects){
    for (int i = 0; i < nb_body; i++){
        SDL_FRect temp_rect = {body_list[i].pos.x, body_list[i].pos.y, 5., 5.};
        rects[i] = temp_rect;
    }
}

void draw_frame(body* body_list, int nb_body, SDL_Renderer* renderer, SDL_FRect* rects){
    //clears screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //updates the rectangle position
    for (int i = 0; i < nb_body; i++){
        rects[i].x = body_list[i].pos.x;
        rects[i].y = body_list[i].pos.y;
    }
    //draws the rectangles, refreshes screen
    SDL_RenderFillRectsF(renderer, rects, nb_body);
    SDL_RenderPresent(renderer);
}

enum keyboard_action check_keyboard(){
    SDL_Event event;
    while( SDL_PollEvent( &event ) )
        {
            if (event.type == SDL_QUIT)
            {
                return EXIT_SIM;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_p:
                    return TOGGLE_SIM;
                case SDLK_n:
                    return NEXT_FRAME;
                default:
                    break;
                }
            }
        }
    return NO_EVENT;
}
