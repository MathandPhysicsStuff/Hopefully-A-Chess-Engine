#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


enum {e, P, N, B, R, Q, K, p, n, b, r, q, k, o};


typedef struct DrawGame
{

    int screen_width, screen_height;
    int scale;
    int start_x, start_y;

} DrawGame;

//Draw board and pieces
void draw_board(SDL_Renderer* renderer, DrawGame* G);
void print_board(int *board, char *pieces);

//logic: rules of chess

//Engine: search eval;

#endif
