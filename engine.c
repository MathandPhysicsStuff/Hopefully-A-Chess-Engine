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


    int source_square = get_move_source(move);
    int target_square = get_move_target(move);
    int promoted_piece = get_move_promote(move);

    board[target_square] = board[source_square];
    board[source_square] = e;
    

    if (promoted_piece)
    {
        board[target_square] = promoted_piece;
    }

    printf("move: %s %s\n", square_to_coords[source_square],  square_to_coords[target_square]);

}



























