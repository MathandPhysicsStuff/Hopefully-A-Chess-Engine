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

void generate_moves(int *board, GameRules *GR)
{
    int i, square, pawn_offset, target_square;

    for (square = 0; square < 128; square++)
    {
        if (!(square & 0x88))
        {
            if (GR->side_to_move == White)
            {
                if (board[square] == P)
                {
                    if (!(!(square - 16) & 0x88) && (board[square - 16] == e))
                    {
                        if (square >= a7 && square <= h7)
                        {
                            printf("%s %s=Q\n", square_to_coords[square], square_to_coords[square - 16]);
                            printf("%s %s=N\n", square_to_coords[square], square_to_coords[square - 16]);
                            printf("%s %s=R\n", square_to_coords[square], square_to_coords[square - 16]);
                            printf("%s %s=B\n", square_to_coords[square], square_to_coords[square - 16]);
                        }
                        
                        else
                        {
                            printf("%s %s\n", square_to_coords[square], square_to_coords[square - 16]);
                            if (square >= a2 && square <= h2 && board[square - 32] == e)
                            {
                                printf("%s %s\n", square_to_coords[square], square_to_coords[square - 32]);
                            }
                        }
                    }

                    for (i = 0; i < 4; i++)
                    {
                        pawn_offset = bishop_offsets[i];

                        if (pawn_offset < 0)
                        {
                            target_square = square + pawn_offset;

                            if(!(target_square & 0x88))
                            {
                                if((square >= a7 && square <= h7) && (board[target_square] >= p && board[target_square] <= k))
                                {
                                    printf("%sx%s=Q\n", square_to_coords[square], square_to_coords[target_square]);
                                    printf("%sx%s=N\n", square_to_coords[square], square_to_coords[target_square]);
                                    printf("%sx%s=R\n", square_to_coords[square], square_to_coords[target_square]);
                                    printf("%sx%s=B\n", square_to_coords[square], square_to_coords[target_square]);
                                }

                                if(board[target_square] >= p && board[target_square] <= k)
                                {
                                    printf("%sx%s\n", square_to_coords[square], square_to_coords[target_square]);
                                }

                                if(target_square == GR->enpassant)
                                {
                                    printf("%sx%s\n", square_to_coords[square], square_to_coords[target_square]);
                                }
                            }
                        }
                    }
                }
            }

            else
            {
                if (board[square] == p)
                {
                    if (!(!(square + 16) & 0x88) && (board[square + 16] == e))
                    {
                        if (square >= a2 && square <= h2)
                        {
                            printf("%s %s=Q\n", square_to_coords[square], square_to_coords[square + 16]);
                            printf("%s %s=N\n", square_to_coords[square], square_to_coords[square + 16]);
                            printf("%s %s=R\n", square_to_coords[square], square_to_coords[square + 16]);
                            printf("%s %s=B\n", square_to_coords[square], square_to_coords[square + 16]);
                        }
                        
                        else
                        {
                            printf("%s %s\n", square_to_coords[square], square_to_coords[square + 16]);
                            if (square >= a7 && square <= h7 && board[square + 32] == e)
                            {
                                printf("%s %s\n", square_to_coords[square], square_to_coords[square + 32]);
                            }
                        }
                    }

                    for (i = 0; i < 4; i++)
                    {
                        pawn_offset = bishop_offsets[i];

                        if (pawn_offset > 0)
                        {
                            target_square = square + pawn_offset;

                            if(!(target_square & 0x88))
                            {
                                if((square >= a2 && square <= h2) && (board[target_square] >= P && board[target_square] <= K))
                                {
                                    printf("%sx%s=Q\n", square_to_coords[square], square_to_coords[target_square]);
                                    printf("%sx%s=N\n", square_to_coords[square], square_to_coords[target_square]);
                                    printf("%sx%s=R\n", square_to_coords[square], square_to_coords[target_square]);
                                    printf("%sx%s=B\n", square_to_coords[square], square_to_coords[target_square]);
                                }

                                if(board[target_square] >= K && board[target_square] <= K)
                                {
                                    printf("%sx%s\n", square_to_coords[square], square_to_coords[target_square]);
                                }

                                if(target_square == GR->enpassant)
                                {
                                    printf("%sx%s\n", square_to_coords[square], square_to_coords[target_square]);
                                }
                            }
                        }
                    }

                }
            }
        }
    }
}



















