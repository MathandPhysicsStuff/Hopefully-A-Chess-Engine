#include <stdio.h>

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

    Moves move_list;
    move_list.move_count = 0;
    
    SDL_Rect piece_src_rect = {0, 0, 60, 60}; 
    SDL_Rect piece_dst_rect = {0, 0, G.scale, G.scale}; 

    char test_position[] = "8/4n3/8/8/p3q2P/8/8/4N3 b - - 0 1";
    parse_FEN(board, test_position, &GR); 

    print_board(board, &GR);
    //generate_moves(board, &GR);
    //print_attack_squares(board, &GR);

    int move, move1, move2;
    move1 = encode_move(e2, e4, 0, 0, 0, 0, 0);
    move2 = encode_move(e7, e5, 0, 0, 0, 0, 0);

    add_move(&move_list, move1);
    add_move(&move_list, move2);
    
    printf("\n");
    for (int i = 0; i < move_list.move_count; i++)
    {
        int print_move = move_list.moves[i];
        printf("%d\n", print_move);
    }
    
    //return 0;

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


        draw_board(renderer, &G);
        draw_pieces(board, renderer, &G, texturePGN, piece_dst_rect, piece_src_rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    //freeing stuff 
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}















