#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/*
    0000 0000 0000 0000 0111 1111 source square
    0000 0000 0011 1111 1000 0000 target square 
    0000 0011 1100 0000 0000 0000 promotion piece
    0000 0100 0000 0000 0000 0000 capture flag
    0000 1000 0000 0000 0000 0000 double pawn push flag
    0001 0000 0000 0000 0000 0000 enpassant flag
    0010 0000 0000 0000 0000 0000 caslting flag
*/

#define encode_move(source, target, promote, capture, double_pawn, enpassant, castling) \
(                           \
    (source) |              \
    (target << 7)   |       \
    (promote << 14) |       \
    (capture << 18) |       \
    (double_pawn << 19) |   \
    (enpassant << 20)   |   \
    (castling << 21)        \
)

#define get_move_source(move) (move & 0x7F)

#define get_move_target(move) ((move >> 7) & 0x7F)

#define get_move_promote(move) ((move >> 14) & 0xF)

#define get_move_capture(move) ((move >> 18) & 0x1)

#define get_move_double_pawn(move) ((move >> 19) & 0x1)

#define get_move_enpassant(move) ((move >> 20) & 0x1)

#define get_move_castling(move) ((move >> 21) & 0x1)

enum boolean {False, TRUE};

enum pieces {e, P, N, B, R, Q, K, p, n, b, r, q, k, o};

enum castling {KC = 1, QC = 2, kc = 4, qc = 8};

enum side {White, Black};

enum capture_flags {all_moves, only_captures};

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

static char *square_to_coords[] = 
{
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "i8", "j8", "k8", "l8", "m8", "n8", "o8", "p8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "i7", "j7", "k7", "l7", "m7", "n7", "o7", "p7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "i6", "j6", "k6", "l6", "m6", "n6", "o6", "p6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "i5", "j5", "k5", "l5", "m5", "n5", "o5", "p5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "i4", "j4", "k4", "l4", "m4", "n4", "o4", "p4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "i3", "j3", "k3", "l3", "m3", "n3", "o3", "p3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "i2", "j2", "k2", "l2", "m2", "n2", "o2", "p2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "i1", "j1", "k1", "l1", "m1", "n1", "o1", "p1"
};

static int char_pieces[] =
{
    ['P'] = P,
    ['N'] = N,
    ['B'] = B,
    ['R'] = R,
    ['Q'] = Q,
    ['K'] = K,
    ['p'] = p,
    ['n'] = n,
    ['b'] = b,
    ['r'] = r,
    ['q'] = q,
    ['k'] = k
};

static int promoted_pieces[] =
{
        [Q] = 'q',
        [R] = 'r',
        [B] = 'b',
        [N] = 'n',
        [q] = 'q',
        [r] = 'r',
        [b] = 'b',
        [n] = 'n'
};



static char ascii_pieces[14] = ".PNBRQKpnbrqko";

static int knight_offsets[8] = {33, 31, 18, 14, -33, -31, -18, -14};
static int bishop_offsets[4] = {17, 15, -17, -15};
static int rook_offsets[4]  = {1, -1, 16, -16};
static int queen_offsets[8] = {1, -1, 16, -16, 17, 15, -17, -15};
static int king_offsets[8] = {1, -1, 16, -16, 17, 15, -17, -15};


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
    int king_square[2];

}GameRules;

typedef struct Moves
{
    int moves[256];
    int move_count;

}Moves;


//Draw board and pieces
void print_board(int *board, GameRules *GR);
void print_attack_squares(int *board, GameRules *GR);
void draw_board(SDL_Renderer* renderer, DrawGame* G);
void draw_pieces(int *board, SDL_Renderer *renderer, DrawGame *G, SDL_Texture *image, SDL_Rect piece_src_rect, SDL_Rect piece_dst_rect);
void reset_board(int *board, GameRules *GR);
void parse_FEN(int *board, char *fen, GameRules *GR);
void print_move_list(Moves *move_list);

//logic: rules of chess
int is_square_attacked(int *board, int side_to_move, int square);
void generate_moves(int *board, GameRules *GR, Moves *move_list);
void add_move(Moves *move_list, int move);

//Engine: search eval;
int make_move(int *board, GameRules *GR, int move, int capture_flag);
void perft_driver(int *board, GameRules *GR, int depth);

#endif



