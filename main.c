#include <stdio.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "header.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 860;
const int SCREEN_HEIGHT = 576;

int board[128] =
{
    r, n, b, q, k, b, n, r,  o, o, o, o, o, o, o, o,
    p, p, p, p, p, p, p, p,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,  o, o, o, o, o, o, o, o,
    P, P, P, P, P, P, P, P,  o, o, o, o, o, o, o, o,
    R, N, B, Q, K, B, N, R,  o, o, o, o, o, o, o, o
};

char start_position[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
char debug_position[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL2 video failed to initialize: \n", SDL_GetError());
    else printf("System is ready to go!\n");

    window = SDL_CreateWindow("Hello SDL",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED);

    int flags = IMG_INIT_PNG;
    int init_status = IMG_Init(flags);
    if ((init_status & flags) != flags) printf("image init error\n"); 

    SDL_Surface* image;
    image = IMG_Load("ChessPiecesArray.png");
    if (!image) { printf("Image not loaded.\n"); }

    SDL_Texture* texturePGN = SDL_CreateTextureFromSurface(renderer, image);

    DrawGame G = 
    {
        G.screen_width = SCREEN_WIDTH,
        G.screen_height = SCREEN_HEIGHT,
        G.start_x = 32,
        G.start_y = 32,
        G.scale = 64
    };

    GameRules GR =
    {
        GR.side_to_move = White,
        GR.enpassant = no_square,
        GR.castling = 0,

    };
    GR.king_square[0] = e1;
    GR.king_square[1] = e8;

    SDL_Rect piece_src_rect = {0, 0, 60, 60}; 
    SDL_Rect piece_dst_rect = {0, 0, G.scale, G.scale}; 

    char test_position[] = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ";
    char test2_position[] = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
    parse_FEN(board, start_position, &GR); 

    int depth = 5;
    long node = 0;
    
    int BOOL = 0; 
    
    if (BOOL == 0)
    {
        perft_driver(board, &GR, depth, &node);
        printf("%ld\n", node);
    } 
    
    if (BOOL == 1)
    {
    SDL_bool running = SDL_TRUE;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = SDL_FALSE;
                break;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = SDL_FALSE;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_perft_driver(board, &GR, depth, &node, renderer, &G, texturePGN, piece_dst_rect, piece_src_rect);

        //draw_board(renderer, &G);
        //draw_pieces(board, renderer, &G, texturePGN, piece_dst_rect, piece_src_rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    }

    //freeing stuff 
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}















