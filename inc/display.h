/**
 * @file display.h
 * @author Grégory Brivady (gregory.brivady@gmail.com)
 * @brief 
 * @version 0.2
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL.h>
#include "body.h"

enum keyboard_action {NO_EVENT, NEXT_FRAME, TOGGLE_SIM, EXIT_SIM};

void start_graphics(int width, int height, SDL_Window* window, SDL_Renderer** p_renderer);

void end_graphics(SDL_Window* window);

void init_frames(body** body_list, int nb_body, SDL_FRect* rects);

void draw_frame(body** body_list, int nb_body, SDL_Renderer* renderer, SDL_FRect* rects);

enum keyboard_action check_keyboard();

#ifdef __cplusplus
}
#endif

#endif