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
    int i, square, piece_offset, target_square;

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
                        piece_offset = bishop_offsets[i];

                        if (piece_offset < 0)
                        {
                            target_square = square + piece_offset;

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

                if (board[square] == K && board[e1] == K)
                {
                    if (GR->castling & KC)
                    {
                        if (board[f1] == e && board[g1] == e && board[h1] == R)
                        {
                            GR->side_to_move = Black;
                            if(is_square_attacked(board, GR, e1) == 0 && is_square_attacked(board, GR, f1) == 0)
                                printf("0-0\n");
                                GR->side_to_move = White;
                        }
                    }

                    if (GR->castling & QC)
                    {
                        if (board[d1] == e && board[c1] == e && board[b1] == e && board[a1] == R)
                        {
                            GR->side_to_move = Black;
                            if(is_square_attacked(board, GR, e1) == 0 && is_square_attacked(board, GR, d1) == 0)
                                printf("0-0-0\n");
                                GR->side_to_move = White;
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
                        piece_offset = bishop_offsets[i];

                        if (piece_offset > 0)
                        {
                            target_square = square + piece_offset;

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

                if (board[square] == k && board[e8] == k)
                {
                    if (GR->castling & kc)
                    {
                        if (board[f8] == e && board[g8] == e && board[h8] == r)
                        {
                            GR->side_to_move = White;
                            if(is_square_attacked(board, GR, e8) == 0 && is_square_attacked(board, GR, f8) == 0)
                                printf("0-0\n");
                                GR->side_to_move = Black;
                        }
                    }

                    if (GR->castling & qc)
                    {
                        if (board[d8] == e && board[c8] == e && board[b8] == e && board[a8] == r)
                        {
                            GR->side_to_move = White;
                            if(is_square_attacked(board, GR, e8) == 0 && is_square_attacked(board, GR, d8) == 0)
                                printf("0-0-0\n");
                                GR->side_to_move = Black;
                        }
                    }
                }
            }

            if (GR->side_to_move == White ? board[square] == N : board[square] == n)
            {
                for(i = 0; i < 8; i++)
                {
                    target_square = square + knight_offsets[i];
                    piece_offset = board[target_square];

                    if (!(target_square & 0x88))
                    {
                        if (
                            GR->side_to_move == White ?
                            (piece_offset == e || (piece_offset >= p && piece_offset <= k)) :
                            (piece_offset == e || (piece_offset >= P && piece_offset <= K))
                            )
                        {
                            if (piece_offset != e)
                                printf("Nx%s\n", square_to_coords[target_square]);
                            else
                                printf("N%s\n", square_to_coords[target_square]);
                        }
                    }
                }
            }

            if (GR->side_to_move == White ? board[square] == K : board[square] == k)
            {
                for(i = 0; i < 8; i++)
                {
                    target_square = square + king_offsets[i];
                    piece_offset = board[target_square];

                    if (!(target_square & 0x88))
                    {
                        if (
                            GR->side_to_move == White ?
                            (piece_offset == e || (piece_offset >= p && piece_offset <= k)) :
                            (piece_offset == e || (piece_offset >= P && piece_offset <= K))
                            )
                        {
                            if (piece_offset != e)
                                printf("Kx%s\n", square_to_coords[target_square]);
                            else
                                printf("K%s\n", square_to_coords[target_square]);
                        }
                    }
                }
            }

            if (GR->side_to_move == White ?
                (board[square] == B || board[square] == Q) :
                (board[square] == b || board[square] == q)
               )
            {
                for (i = 0; i < 4; i++)
                {
                    target_square = square + bishop_offsets[i];
                    
                    while (!(target_square & 0x88))
                    {
                        piece_offset = board[target_square];

                        if (GR->side_to_move == White ?
                            (piece_offset >= P && piece_offset <= K) :
                            (piece_offset >= p && piece_offset <= k)
                           )
                        {
                            break; 
                        }

                        if (GR->side_to_move == White ?
                            (piece_offset >= p && piece_offset <= k) :
                            (piece_offset >= P && piece_offset <= K)
                           )
                        {
                            if(board[square] == b || board[square] == B) printf("Bx%s\n", square_to_coords[target_square]);
                            if(board[square] == q || board[square] == Q) printf("Qx%s\n", square_to_coords[target_square]);
                            break; 
                        }


                        if (piece_offset == e)
                        {
                            if(board[square] == b || board[square] == B) printf("B%s\n", square_to_coords[target_square]);
                            if(board[square] == q || board[square] == Q) printf("Q%s\n", square_to_coords[target_square]);
                        }

                        target_square += bishop_offsets[i];
                    }
                }
            }

            if (GR->side_to_move == White ?
                (board[square] == R || board[square] == Q) :
                (board[square] == r || board[square] == q)
               )
            {
                for (i = 0; i < 4; i++)
                {
                    target_square = square + rook_offsets[i];
                    
                    while (!(target_square & 0x88))
                    {
                        piece_offset = board[target_square];

                        if (GR->side_to_move == White ?
                            (piece_offset >= P && piece_offset <= K) :
                            (piece_offset >= p && piece_offset <= k)
                           )
                        {
                            break; 
                        }

                        if (GR->side_to_move == White ?
                            (piece_offset >= p && piece_offset <= k) :
                            (piece_offset >= P && piece_offset <= K)
                           )
                        {
                            if(board[square] == r || board[square] == R) printf("Rx%s\n", square_to_coords[target_square]);
                            if(board[square] == q || board[square] == Q) printf("Qx%s\n", square_to_coords[target_square]);
                            break; 
                        }


                        if (piece_offset == e)
                        {
                            if(board[square] == r || board[square] == R) printf("R%s\n", square_to_coords[target_square]);
                            if(board[square] == q || board[square] == Q) printf("Q%s\n", square_to_coords[target_square]);
                        }

                        target_square += rook_offsets[i];
                    }
                }
            }
        }
    }
}

void add_move(Moves *move_list, int move)
{
    move_list->moves[move_list->move_count] = move;
    move_list->move_count++;
}
















