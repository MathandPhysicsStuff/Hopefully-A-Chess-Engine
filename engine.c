#include "header.h"

int make_move(int *board, GameRules *GR, int move)
{
    int board_copy[128];
    GameRules Copy;

    memcpy(board_copy, board, 512);
    Copy.side_to_move = GR->side_to_move;
    Copy.enpassant = GR->enpassant;
    Copy.castling = GR->castling;
    memcpy(Copy.king_square, GR->king_square, 8);

}



























