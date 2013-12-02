#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
typedef struct
{
    SDL_Surface *Musique;
    SDL_Surface *SonClic;
    SDL_Surface *Quitter;
    SDL_Surface* fond;

    SDL_Rect PositionMusique;
    SDL_Rect PositionSonClic;
    SDL_Rect PositionQuitter;
    TTF_Font *police ;
} ComposantsOptions;
void ComposantsPourOptions(ComposantsOptions *);
void BlitterComposantsOptions(ComposantsOptions*);
void LibererComposantsOptions(ComposantsOptions*);
void Options();
