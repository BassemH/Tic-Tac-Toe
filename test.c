#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include"option.h"
#include"aide.h"
#include"autre.h"
#include"jeu1.h"
#include"choix.h"
void Comp_menu_princp(copt *cop)
{
    cop->police =TTF_OpenFont("MTCORSVA.TTF", 30);//TTF_OpenFont:ouvre un fichier de police (.ttf)
    TTF_SetFontStyle(cop->police,0);
    SDL_Color couleurNoire = {0,"0","0"};
    TTF_SetFontStyle(cop->police,TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
    cop->jouer = TTF_RenderText_Blended(cop->police, "*****    Jouer     *****",couleurNoire);
    cop->options= TTF_RenderText_Blended(cop->police,"*****   Options   *****", couleurNoire);
    cop->aide= TTF_RenderText_Blended(cop->police,   "*****     Aide      *****", couleurNoire);
    cop->quit= TTF_RenderText_Blended(cop->police,   "*****    Quitter   *****", couleurNoire);
    cop->fond = SDL_LoadBMP("images/morpion.bmp");
    cop->pos_jouer.x=450;
    cop->pos_jouer.y=164;
    cop->pos_options.x=450;
    cop->pos_options.y=204;
    cop->pos_aide.x=450;
    cop->pos_aide.y=244;
    cop->pos_quit.x=450;
    cop->pos_quit.y=284;
}
void Blitterc_p(copt* Charger)
{
    SDL_BlitSurface(Charger->fond, NULL, SDL_GetVideoSurface(), NULL);
    SDL_BlitSurface(Charger->jouer, NULL, SDL_GetVideoSurface(), &Charger->pos_jouer);
    SDL_BlitSurface(Charger->options, NULL, SDL_GetVideoSurface(), &Charger->pos_options);
    SDL_BlitSurface(Charger->aide, NULL, SDL_GetVideoSurface(), &Charger->pos_aide);
    SDL_BlitSurface(Charger->quit, NULL, SDL_GetVideoSurface(), &Charger->pos_quit);
    SDL_Flip(SDL_GetVideoSurface());
}
void LibererComposantsMenuPrincipal(copt* Charger)
{
    SDL_FreeSurface (Charger->jouer);
    SDL_FreeSurface(Charger->options);
    SDL_FreeSurface(Charger->aide);
    SDL_FreeSurface(Charger->quit);
    SDL_FreeSurface(Charger->fond);
    TTF_CloseFont(Charger->police);
}
int collision( int clique_X, int clique_Y, SDL_Rect position_Figure )
{
    if ( clique_X > (position_Figure.x)  &&  clique_X < (position_Figure.x + position_Figure.w) && clique_Y > position_Figure.y &&  clique_Y < (position_Figure.y + position_Figure.h))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main(int argc, char *argv[])
{
	SDL_Event event;
	SDL_Rect position;
	int continuer = 1;
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    TTF_Init();
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());/*S'il y a eu une erreur au
        démarrage de SDL_ttf, un fichier stderr.txt sera créé contenant un message explicatif de l'erreur.la fonction
        TTF_GetError() renvoie le dernier message d'erreur de SDL_ttf.C'est pour cela qu'on l'utilise dans le fprintf.*/
        exit(EXIT_FAILURE);
    }
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    // create a new window
    SDL_Surface *ecran = SDL_SetVideoMode(1150,750,32,SDL_HWSURFACE | SDL_DOUBLEBUF);//602,402
    if ( !ecran )
    {
        printf("Unable to set 602x402 video: %s\n", SDL_GetError());
        return 1;
    }
	SDL_WM_SetCaption("Menu de jeu TIC TAC TOE", NULL);
    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("images/morpion.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    // centre the bitmap on screen
    SDL_Rect font;
    font.x = (ecran->w-bmp->w) / 2;
    font.y = (ecran->h-bmp->h) / 2;
    Musiques m;
    Mix_AllocateChannels(2);
    m.musique= Mix_LoadMUS("musiques/musique1.mp3");
    m.Clic= Mix_LoadWAV("musiques/clic1.wav");
    Mix_VolumeMusic(200);
    Mix_PlayMusic(m.musique,-1);
    Mix_PlayChannel(0,m.Clic,0);
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                position.x = event.motion.x ;
                position.y = event.motion.y ;
                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym==SDLK_s)
                    continuer= 0;
                break;
		}
        // clear screen
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
		 // draw bitmap
        SDL_BlitSurface(bmp,0,ecran,&font);
		SDL_Flip(ecran);
        MenuPrincipal();
	}
	Mix_FreeMusic(m.musique);
    Mix_FreeChunk(m.Clic);
    Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}
void MenuPrincipal()
{
    SDL_Event event;
    int VariablePourSon=0;
    copt Charger;
    Comp_menu_princp(&Charger);
    Blitterc_p(&Charger);
    int continuer=1;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch( event.type )
        {
        case SDL_QUIT:
            continuer=0;
            LibererComposantsMenuPrincipal(&Charger);
            exit(0);
            break;
        case SDL_MOUSEBUTTONUP:
            if (collision(event.button.x, event.button.y, Charger.pos_jouer))
            {
                continuer=0;
                LibererComposantsMenuPrincipal(&Charger);
                Choix();
            }
            else if (collision(event.button.x,event.button.y, Charger.pos_options))
            {
                continuer=0;
                LibererComposantsMenuPrincipal(&Charger);
                Options();
            }
            else if (collision(event.button.x,event.button.y, Charger.pos_aide))
            {
                continuer=0;
                LibererComposantsMenuPrincipal(&Charger);
                Aide();
            }
             else if (collision(event.button.x,event.button.y, Charger.pos_quit))
            {
                continuer=0;
                LibererComposantsMenuPrincipal(&Charger);
                exit(0);
            }
            break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch (event.key.keysym.sym)
            {
            case SDLK_s:
                Blitterc_p(&Charger);
                ModifierSon (&VariablePourSon);
                break;
            default:
                break;
            }
        }
    }
}
