#include "header.h"

int make_move(int *board, GameRules *GR, int move, int capture_flag)
{
    int board_copy[128];
    GameRules Copy;

    if (capture_flag == all_moves)
    {
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
        int castling = get_move_castling(move);

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

        if (castling)
        {
            switch (target_square)
            {
                case g1:
                    board[f1] = board[h1];
                    board[h1] = e;
                    break;

                case c1:
                    board[d1] = board[a1];
                    board[a1] = e;
                    break;

                case g8:
                    board[f8] = board[h8];
                    board[h8] = e;
                    break;

                case c8:
                    board[d8] = board[a8];
                    board[a8] = e;
                    break;
            }
        }

        if (board[target_square] == K || board[target_square] == k)
        {
            GR->king_square[GR->side_to_move] = target_square;
        }

        if (board[e1] != K) GR->castling &= 0xC;
        if (board[a1] != R) GR->castling &= 0xD;
        if (board[h1] != R) GR->castling &= 0xE;
        if (board[e8] != k) GR->castling &= 0x3;
        if (board[a8] != r) GR->castling &= 0xB;
        if (board[h8] != r) GR->castling &= 0x7;

        GR->side_to_move ^= 1; 

        if (is_square_attacked(board, GR->side_to_move, GR->king_square[GR->side_to_move ^ 1]))
        {
            memcpy(board, board_copy, 512);
            GR->side_to_move = Copy.side_to_move;
            GR->enpassant = Copy.enpassant;
            GR->castling = Copy.castling;
            memcpy(GR->king_square, Copy.king_square, 8);
           
            return 0;
        }

        else
            return 1;
    }

    else
    {
        if (get_move_capture(move))
        {
            make_move(board, GR, move, all_moves);
        }

        else
        {
            return 0;
        }
    }

    //printf("\nmove: %s %s\n", square_to_coords[source_square],  square_to_coords[target_square]);
}



























