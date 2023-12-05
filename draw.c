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

void print_board(int *board, char *pieces, char **square_to_coords, GameRules *R)
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
                printf("%c ", pieces[board[square]]); 
        }
        printf("\n");
    }
    printf("\n    a b c d e f g h\n");
    printf("\n");
    
    printf(" Side to move: %s\n", (R->side_to_move == White) ? "White": "Black");
    printf(" Castling: %c", (R->castling & KC) ? 'K' : '-');
    printf("%c", (R->castling & QC) ? 'Q' : '-');
    printf("%c", (R->castling & kc) ? 'k' : '-');
    printf("%c\n", (R->castling & qc) ? 'q' : '-');

    printf(" Enpassant: %s\n", square_to_coords[R->enpassant]);
}

void reset_board(int *board, GameRules *R)
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
    R->side_to_move = White;
    R->castling = 0;
    R->enpassant = no_square;
}


void parse_FEN(int *board, int *char_pieces, char **square_to_coords, char *fen, GameRules *R)
{
    int rank, file, square;
    
    reset_board(board, R);

    for (rank = 0; rank < 8; rank++)
    {
        for (file = 0; file < 16; file++)
        {
            square = 16*rank + file;

            if (!(square & 0x88))
            {
                if ((*fen >= 'a' && *fen <= 'z') || (*fen >= 'A' && *fen <= 'Z'))
                {
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

    if (*fen == 'w') R->side_to_move = White;
    if (*fen == 'b') R->side_to_move = Black;

    *fen++;
    *fen++;

    while (*fen != ' ')
    {
        switch(*fen)
        {
            case 'K': R->castling |= KC; break;
            case 'Q': R->castling |= QC; break;
            case 'k': R->castling |= kc; break;
            case 'q': R->castling |= qc; break;
            case '-': break;

        }
        *fen++;
    }

    *fen++;

    if (*fen != '-')
    {
        file = fen[0] - 'a';
        rank = 8 - (fen[1] - '0');

        R->enpassant = 16*rank + file;
        printf("%i\n", R->enpassant);
    }

    else R->enpassant = no_square;

    printf("%s\n", fen);
    printf("%c\n", *fen);
}
























