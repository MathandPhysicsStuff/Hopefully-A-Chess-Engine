#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct DrawGame
{

    int screen_width, screen_height;
    int scale;
    int start_x, start_y;

} DrawGame;

void draw_board(SDL_Renderer* renderer, DrawGame* G);


#endif
