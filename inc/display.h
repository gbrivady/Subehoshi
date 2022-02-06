/**
 * @file display.h
 * @author Grégory Brivady (gregory.brivady@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#define SDL_MAIN_HANDLED
#include "body.h"
#include <stdio.h>
#include <SDL.h>

enum keyboard_action {NO_EVENT, NEXT_FRAME, TOGGLE_SIM, EXIT_SIM};

void start_graphics(int width, int height, SDL_Window* window, SDL_Renderer** p_renderer);

void end_graphics(SDL_Window* window, SDL_Renderer** p_renderer);

void init_frames(body** body_list, int nb_body, SDL_FRect* rects);

void draw_frame(body** body_list, int nb_body, SDL_Renderer* renderer, SDL_FRect* rects);


enum keyboard_action check_keyboard();

#endif