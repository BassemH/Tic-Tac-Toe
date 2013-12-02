#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
void ModifierSon (int*VariablePourSon)
{
    SDL_Rect PositionSon;
    PositionSon.x=10;/*un peu a côté du coin en haut à gauche*/
    PositionSon.y=10;
    int l;
    SDL_Surface *Son[3];
    //Son[0]=ChargerImage( "SonFort.gif" );/*On charge les images*/
    /*Son[1]=ChargerImage( "SonMoyen.gif");
    Son[2]=ChargerImage( "SonCoupe.gif");*/
    SDL_BlitSurface(Son[*VariablePourSon], NULL, SDL_GetVideoSurface(), &PositionSon);
    Mix_VolumeMusic(128-(*VariablePourSon)*64);
    Mix_Volume(1, 128-(*VariablePourSon)*64);
    SDL_Flip(SDL_GetVideoSurface());
    if (*VariablePourSon==2)
    {
        *VariablePourSon=-1;
    }
    (*VariablePourSon)++;
    for (l=0; l<3; l++)
    {
        SDL_FreeSurface(Son[l]);
    }
}
