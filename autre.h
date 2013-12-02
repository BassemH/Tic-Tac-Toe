#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL_mixer.h>
typedef struct
{
    SDL_Surface *jouer;
    SDL_Surface *options;
    SDL_Surface *aide;
    SDL_Surface *quit;
    SDL_Surface *fond;

    SDL_Rect pos_jouer;
    SDL_Rect pos_options;
    SDL_Rect pos_aide;
    SDL_Rect pos_quit;
    SDL_Rect pos_fond;
    TTF_Font *police ;
} copt;
typedef struct
{
    Mix_Music *musique;
    Mix_Chunk *Clic;
} Musiques;
void ModifierSon (int*Var_Son);
