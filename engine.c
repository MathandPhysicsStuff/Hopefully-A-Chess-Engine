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
    int enpassant = get_move_enpassant(move);
    int double_pawn = get_move_double_pawn(move);

    board[target_square] = board[source_square];
    board[source_square] = e;
    

    if (promoted_piece)
    {
        board[target_square] = promoted_piece;
    }

    if (enpassant)
    {
        (GR->side_to_move == White ? (board[target_square + 16] = e) : (board[target_square - 16] = e));
    }

    GR->enpassant = no_square;

    if (double_pawn)
    {
        (GR->side_to_move == White ? (GR->enpassant = target_square + 16) : (GR->enpassant = target_square - 16));
    }

    printf("\nmove: %s %s\n", square_to_coords[source_square],  square_to_coords[target_square]);

}



























