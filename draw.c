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

void print_board(int *board, char *pieces)
{
    int i, j, piece;
    int row = 8, col = 8, shift = 0;

    printf("\n"); 
    for (i = 0; i < row; i++)
    {
        printf(" %d  ", 8 - i);
        for (j = 0; j < col; j++)
        {
            piece = board[i+shift + j];
            printf("%c ", pieces[piece]); 
        }
        shift += 15;
        printf("\n");
    }
    printf("\n    a b c d e f g h\n");
}























