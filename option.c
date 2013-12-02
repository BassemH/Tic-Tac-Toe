#include"option.h"
#include"autre.h"
void ComposantsPourOptions(ComposantsOptions *ComposantsPourOptions)
{
    ComposantsPourOptions->police = TTF_OpenFont("SCRIPTBL.TTF", 25);
    TTF_SetFontStyle(ComposantsPourOptions->police, TTF_STYLE_ITALIC);
    SDL_Color couleurNoire = {"#f", 0, "#a"};//{"#f","#c","#c"};
    ComposantsPourOptions->Musique= TTF_RenderText_Blended(ComposantsPourOptions->police, "Musique: Changer", couleurNoire);;
    ComposantsPourOptions->SonClic= TTF_RenderText_Blended(ComposantsPourOptions->police, "Clic : Changer", couleurNoire);
    ComposantsPourOptions->Quitter= TTF_RenderText_Blended(ComposantsPourOptions->police, "Retour au menu Principal", couleurNoire);
    ComposantsPourOptions->fond= SDL_LoadBMP("images/Morpion Options.bmp");

    ComposantsPourOptions->PositionMusique.x=30;
    ComposantsPourOptions->PositionMusique.y=100;
    ComposantsPourOptions->PositionSonClic.x=30;
    ComposantsPourOptions->PositionSonClic.y=200;
    ComposantsPourOptions->PositionQuitter.x=390;
    ComposantsPourOptions->PositionQuitter.y=650;
}
void BlitterComposantsOptions(ComposantsOptions* Charger)
{
    SDL_BlitSurface(Charger->fond, NULL, SDL_GetVideoSurface(), NULL);
    SDL_BlitSurface(Charger->Musique, NULL, SDL_GetVideoSurface(), &Charger->PositionMusique);
    SDL_BlitSurface(Charger->SonClic, NULL, SDL_GetVideoSurface(), &Charger->PositionSonClic);
    SDL_BlitSurface(Charger->Quitter, NULL, SDL_GetVideoSurface(), &Charger->PositionQuitter);
    SDL_Flip(SDL_GetVideoSurface());
}
void LibererComposantsOptions(ComposantsOptions* Charger)
{
    SDL_FreeSurface (Charger->Musique);
    SDL_FreeSurface(Charger->SonClic);
    SDL_FreeSurface(Charger->Quitter);
    SDL_FreeSurface(Charger->fond);
    TTF_CloseFont(Charger->police);
}
void LibererSons(Musiques* m)
{
    Mix_FreeMusic(m->musique);
    Mix_FreeChunk(m->Clic);
}
void Options()
{
    SDL_Event event;
    int Var_Son=0;
    char NomMusique[40]= "";
    char NomClic[40]= "";
    int NumeroMusique=2;/*On initialise à 2 pour que le son change directement :*/
    int NumeroClic=2;/*pour éviter de repasser deux fois le même */
    int continuer=1;
    ComposantsOptions Charger;
    ComposantsPourOptions(&Charger);
    BlitterComposantsOptions(&Charger);
    Musiques m;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch( event.type )
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_MOUSEBUTTONUP:

            if (collision(event.button.x,event.button.y, Charger.PositionMusique ))
            {
                Mix_FreeMusic(m.musique);
                sprintf(NomMusique, "musiques/musique%d.mp3", NumeroMusique);
                m.musique= Mix_LoadMUS(NomMusique);
                if (NumeroMusique==3)
                {
                    NumeroMusique=0;
                }
                NumeroMusique++;
                Mix_PlayMusic(m.musique, -1);

            }
            else if (collision(event.button.x,event.button.y, Charger.PositionSonClic ))
            {
                Mix_FreeChunk(m.Clic);
                sprintf(NomClic, "musiques/clic%d.wav", NumeroClic);
                m.Clic= Mix_LoadWAV(NomClic);
                if (NumeroClic==4)
                {
                    NumeroClic=0;
                }
                (NumeroClic)++;
                Mix_PlayChannel(0, m.Clic, 0);

            }
            else if (collision(event.button.x,event.button.y, Charger.PositionQuitter ))
            {
                continuer=0;
                LibererComposantsOptions(&Charger);
                MenuPrincipal();
            }
            break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
            case SDLK_s:
                BlitterComposantsOptions(&Charger);
                ModifierSon (&Var_Son);
                break;
            default:
                break;
            }
        }
    }
}
