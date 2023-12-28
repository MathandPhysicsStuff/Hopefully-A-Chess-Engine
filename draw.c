#include "header.h"

void draw_board(SDL_Renderer* renderer, DrawGame* G)
{
    int i, j;
    int row = 8;
    int col = 8;
    int square_counter = 0;
    SDL_Rect square;
    square.x = G->start_x;
    square.y = G->start_y - 32;
    square.w = G->scale;
    square.h = G->scale;

    SDL_Rect boarder;
    boarder.x = 0;
    boarder.y = 0;
    boarder.w = G->screen_width;
    boarder.h = G->screen_height;

    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
    SDL_RenderDrawRect(renderer, &boarder);

    for (i = 0; i < row; i++)
    {
        square.x = G->start_x;
        for (j = 0; j < col; j++)
        {
            if (square_counter % 2 == 0) SDL_SetRenderDrawColor(renderer, 204, 183, 174, 255);
            else SDL_SetRenderDrawColor(renderer, 112, 102, 119, 255);
    
            SDL_RenderFillRect(renderer, &square);

            square.x += G->scale;
            square_counter += 1;
        }
        square.y += G->scale;
        square_counter += 1;
    }
}

void draw_pieces(int *board, SDL_Renderer *renderer, DrawGame *G, SDL_Texture *image, SDL_Rect piece_src_rect, SDL_Rect piece_dst_rect)
{
    int rank, file, square;
    
    piece_src_rect.x = G->start_x; 
    piece_src_rect.y = G->start_y - 32; 

    for (rank = 0; rank < 8; rank++)
    {
        piece_src_rect.x = G->start_x;
        for (file = 0; file < 16; file++)
        {
            square = 16*rank + file;

            if (!(square & 0x88))
                //SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                switch(board[square])
                {
                    case P:
                        piece_dst_rect.x = 300;
                        piece_dst_rect.y = 60;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case N:
                        piece_dst_rect.x = 180;
                        piece_dst_rect.y = 60;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case B:
                        piece_dst_rect.x = 240;
                        piece_dst_rect.y = 60;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case R:
                        piece_dst_rect.x = 120;
                        piece_dst_rect.y = 60;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case Q:
                        piece_dst_rect.x = 0;
                        piece_dst_rect.y = 60;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case K:
                        piece_dst_rect.x = 60;
                        piece_dst_rect.y = 60;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case p:
                        piece_dst_rect.x = 300;
                        piece_dst_rect.y = 0;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case n:
                        piece_dst_rect.x = 180;
                        piece_dst_rect.y = 0;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case b:
                        piece_dst_rect.x = 240;
                        piece_dst_rect.y = 0;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case r:
                        piece_dst_rect.x = 120;
                        piece_dst_rect.y = 0;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case q:
                        piece_dst_rect.x = 0;
                        piece_dst_rect.y = 0;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;

                    case k:
                        piece_dst_rect.x = 60;
                        piece_dst_rect.y = 0;
                        SDL_RenderCopy(renderer, image, &piece_dst_rect, &piece_src_rect);
                        break;
                }

            piece_src_rect.x += G->scale;
        }
        piece_src_rect.y += G->scale;
    }
}

void print_board(int *board, GameRules *GR)
{
    int rank, file, square;

    printf("\n"); 
    for (rank = 0; rank < 8; rank++)
    {
        printf(" %d  ", 8 - rank);
        for (file = 0; file < 16; file++)
        {
            square = 16*rank + file;

            if (!(square & 0x88))
                printf("%c ", ascii_pieces[board[square]]); 
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n");
    printf("\n");
    
    printf(" Side to move: %s\n", (GR->side_to_move == White) ? "White": "Black");
    printf(" Castling: %c", (GR->castling & KC) ? 'K' : '-');
    printf("%c", (GR->castling & QC) ? 'Q' : '-');
    printf("%c", (GR->castling & kc) ? 'k' : '-');
    printf("%c\n", (GR->castling & qc) ? 'q' : '-');

    printf(" Enpassant: %s\n", (GR->enpassant == no_square) ? " ": square_to_coords[GR->enpassant]);
    printf(" King square: %s\n", square_to_coords[GR->king_square[GR->side_to_move]]);
}

void print_attack_squares(int *board, GameRules *GR)
{
    int rank, file, square;

    printf("\n"); 

    for (rank = 0; rank < 8; rank++)
    {
        printf(" %d  ", 8 - rank);
        for (file = 0; file < 16; file++)
        {
            square = 16*rank + file;

            if (!(square & 0x88))
                printf("%c ", is_square_attacked(board, GR, square) ? 'x' : '.');
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n");

    printf("\n Attacking side: %s\n", !(GR->side_to_move) ? "White" : "Black");
    printf("\n");
}


void reset_board(int *board, GameRules *GR)
{
    int rank, file, square;

    for (rank = 0; rank < 8; rank++)
    {
        for (file = 0; file < 16; file++)
        {
            square = 16*rank + file;

            if (!(square & 0x88))
                board[square] = e; 
        }
    }
    GR->side_to_move = White;
    GR->castling = 0;
    GR->enpassant = no_square;
}


void parse_FEN(int *board, char *fen, GameRules *GR)
{
    int rank, file, square;
    
    reset_board(board, GR);

    for (rank = 0; rank < 8; rank++)
    {
        for (file = 0; file < 16; file++)
        {
            square = 16*rank + file;

            if (!(square & 0x88))
            {
                if ((*fen >= 'a' && *fen <= 'z') || (*fen >= 'A' && *fen <= 'Z'))
                { 
                    if (*fen == 'K')
                        GR->king_square[White] = square;

                    else if (*fen == 'k')
                        GR->king_square[Black] = square;

                    board[square] = char_pieces[*fen];
                    fen++;
                }
                if (*fen >= '1' && *fen <= '8')
                {
                    if (board[square] == e)
                        file--;

                    file += *fen - '0';
                    fen++;
                }
                if (*fen == '/')
                    fen++;
            }
        }
    }
    
    *fen++;

    if (*fen == 'w') GR->side_to_move = White;
    if (*fen == 'b') GR->side_to_move = Black;

    *fen++;
    *fen++;

    while (*fen != ' ')
    {
        switch(*fen)
        {
            case 'K': GR->castling |= KC; break;
            case 'Q': GR->castling |= QC; break;
            case 'k': GR->castling |= kc; break;
            case 'q': GR->castling |= qc; break;
            case '-': break;

        }
        *fen++;
    }

    *fen++;

    if (*fen != '-')
    {
        file = fen[0] - 'a';
        rank = 8 - (fen[1] - '0');

        GR->enpassant = 16*rank + file;
    }

    else GR->enpassant = no_square;

    //printf("%s\n", fen);
    //printf("%c\n", *fen);
}

void print_move_list(Moves *move_list)
{
    int i, move;

    printf("\n");
    printf(" move  |   promotion | capture | double_pawn | enpassant | castling\n");
    for (i = 0; i < move_list->move_count; i++)
    {
        move = move_list->moves[i];
        printf(" %s-%s |", square_to_coords[get_move_source(move)],  square_to_coords[get_move_target(move)]);
        printf("   %c         |", get_move_promote(move) ? promoted_pieces[get_move_promote(move)] : ' ');
        printf(" %d       |", get_move_capture(move));
        printf(" %d           |", get_move_double_pawn(move));
        printf(" %d         |", get_move_enpassant(move));
        printf(" %d\n", get_move_castling(move));
    }
    printf("\n");
    printf(" number of legal moves: %d\n", move_list->move_count);
}





















