#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

enum pieces {e, P, N, B, R, Q, K, p, n, b, r, q, k, o};

enum castling {KC = 1, QC = 2, kc = 4, qc = 8};

enum side {no_side, White, Black};

enum squares 
{
    a8 = 0, b8, c8, d8, e8, f8, g8, h8,
    a7 = 16, b7, c7, d7, e7, f7, g7, h7,
    a6 = 32, b6, c6, d6, e6, f6, g6, h6,
    a5 = 48, b5, c5, d5, e5, f5, g5, h5,
    a4 = 64, b4, c4, d4, e4, f4, g4, h4,
    a3 = 80, b3, c3, d3, e3, f3, g3, h3,
    a2 = 96, b2, c2, d2, e2, f2, g2, h2,
    a1 = 112, b1, c1, d1, e1, f1, g1, h1, no_square
};


typedef struct DrawGame
{

    int screen_width, screen_height;
    int scale;
    int start_x, start_y;

} DrawGame;

typedef struct GameRules
{
    int side_to_move;
    int enpassant;
    int castling;
}GameRules;

//Draw board and pieces
void print_board(int *board, char *pieces, char **square_to_coords, GameRules *R);
void draw_board(SDL_Renderer* renderer, DrawGame* G);
void reset_board(int *board, GameRules *R);
void parse_FEN(int *board, int *char_pieces, char **square_to_coords, char *fen, GameRules *R);

//logic: rules of chess

//Engine: search eval;

#endif



