#include "header.h"


int is_square_attacked(int *board, GameRules *GR, int square)
{
    int i, j, target_square, target_piece;

    if (GR->side_to_move == White)
    {
        if(!((square + 17) & 0x88) && (board[square + 17] == P)) return 1;
        if(!((square + 15) & 0x88) && (board[square + 15] == P)) return 1;
    }

    else
    {
    if(!((square - 17) & 0x88) && (board[square - 17] == p)) return 1;
    if(!((square - 15) & 0x88) && (board[square - 15] == p)) return 1;
    }
    
    for (i = 0; i < 8; i++)
    {
        target_square = square + knight_offsets[i];
        target_piece = board[target_square];
        
        if (!(target_square & 0x88))
        {
            if(GR->side_to_move == White ? target_piece == N : target_piece == n)
                return 1;
        }
    }
     
    for (i = 0; i < 8; i++)
    {
        target_square = square + king_offsets[i];
        target_piece = board[target_square];
        
        if (!(target_square & 0x88))
        {
            if(GR->side_to_move == White ? target_piece == K : target_piece == k)
                return 1;
        }
    }
    
     
    for (i = 0; i < 4; i++)
    {
        target_square = square + rook_offsets[i];
        
        while(!(target_square & 0x88)) 
        {
            target_piece = board[target_square];

            if(GR->side_to_move == White ? (target_piece == R || target_piece == Q) : (target_piece == r || target_piece == q))
                return 1; 

            if (target_piece != e)
                break;

            target_square += rook_offsets[i];
        }
    }
    
  
    for (i = 0; i < 4; i++)
    {
        target_square = square + bishop_offsets[i];
        
        while(!(target_square & 0x88)) 
        {
            target_piece = board[target_square];

            if(GR->side_to_move == White ? (target_piece == B || target_piece == Q) : (target_piece == b || target_piece == q))
                return 1; 

            if (target_piece != e)
                break;

            target_square += bishop_offsets[i];
        }
    }


    return 0;
}





















