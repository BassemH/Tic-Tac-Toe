#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include"jeu1.h"
void Composants_Pour_FonctionPourJeu3(ComposantsFonctionPourJeu *Composants_Pour_FonctionPourJeu)
{
    Composants_Pour_FonctionPourJeu->police = TTF_OpenFont("PRISTINA.TTF", 25);
    TTF_SetFontStyle(Composants_Pour_FonctionPourJeu->police, TTF_STYLE_ITALIC);
    SDL_Color couleurNoire = {"#f", 0, "#a"};
    Composants_Pour_FonctionPourJeu->croix = SDL_LoadBMP("images/petiteCroix.bmp");
    Composants_Pour_FonctionPourJeu->rond = SDL_LoadBMP("images/PetitRond.bmp");
    Composants_Pour_FonctionPourJeu->PointsCroix= SDL_LoadBMP( "images/petiteCroix.bmp");
    Composants_Pour_FonctionPourJeu->PointsRond = SDL_LoadBMP( "images/PetitRond.bmp");
    Composants_Pour_FonctionPourJeu->grille = SDL_LoadBMP ("images/9colone.bmp");
    Composants_Pour_FonctionPourJeu->TextePoints= SDL_LoadBMP("images/Points.bmp");
    Composants_Pour_FonctionPourJeu->ImageMorpion[0]= SDL_LoadBMP( "images/morpionGrille.bmp" );
    Composants_Pour_FonctionPourJeu->ImageMorpion[1]= SDL_LoadBMP( "images/morpionGrille2.bmp");
    Composants_Pour_FonctionPourJeu->ImageMorpion[2]= SDL_LoadBMP( "images/morpionGrille3.bmp");
    Composants_Pour_FonctionPourJeu->ImageMorpion[2]= SDL_LoadBMP( "images/morpionGrille3.bmp");
    //Composants_Pour_FonctionPourJeu->img= SDL_LoadBMP( "images/play.bmp");
    Composants_Pour_FonctionPourJeu->Quitter= TTF_RenderText_Blended(Composants_Pour_FonctionPourJeu->police, "Retour au menu Principal", couleurNoire);

    Composants_Pour_FonctionPourJeu->positionImageMorpion.x = 900;
    Composants_Pour_FonctionPourJeu->positionImageMorpion.y = 0;
    Composants_Pour_FonctionPourJeu->positionImagePoints.x=30;
    Composants_Pour_FonctionPourJeu->positionImagePoints.y=550;
    Composants_Pour_FonctionPourJeu->position_Grille.x = 250;
    Composants_Pour_FonctionPourJeu->position_Grille.y = 30;
    Composants_Pour_FonctionPourJeu->positionPointsCroix.y=550;/*L'ordonnée des 2 images puisqu'on donne l'abcisse après!*/
    Composants_Pour_FonctionPourJeu->positionPointsRond.y=615;
    Composants_Pour_FonctionPourJeu->pos_Quitter.x=460;
    Composants_Pour_FonctionPourJeu->pos_Quitter.y=650;
   /* pos_img.x = 500;
    pos_img.y = 260;*/
}
void Blits3( int terrain[][9], int Variable_Pour_Image , int pointJoueur1, int pointJoueur2 ,ComposantsFonctionPourJeu* Charger)
{
    int i,j;
    SDL_FillRect(SDL_GetVideoSurface(), NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 255, 255, 255));
    SDL_BlitSurface(Charger->grille, NULL, SDL_GetVideoSurface(), &Charger->position_Grille);
    SDL_BlitSurface(Charger->TextePoints, NULL, SDL_GetVideoSurface(), &Charger->positionImagePoints);
    SDL_BlitSurface(Charger->ImageMorpion[0], NULL, SDL_GetVideoSurface(), &Charger->positionImageMorpion);
    SDL_BlitSurface(Charger->Quitter, NULL, SDL_GetVideoSurface(), &Charger->pos_Quitter);
    for (i = 0 ; i < 9 ; i++)
    {
        for (j = 0 ; j < 9 ; j++)
        {
            Charger->position.x = (i * 66)+265;
            Charger->position.y = (j * 50)+35;

            switch(terrain[i][j])
            {
            case VIDE:
                break;
            case CROIX:
                SDL_BlitSurface(Charger->croix, NULL, SDL_GetVideoSurface(), &Charger->position);
                break;
            case ROND:
                SDL_BlitSurface(Charger->rond, NULL, SDL_GetVideoSurface(), &Charger->position);
                break;
            }
        }
    }
    /*On met à jour et on blit les textes et l'image à gauche de la grille*/
    SDL_BlitSurface(Charger->TextePoints, NULL, SDL_GetVideoSurface(), &Charger->positionImagePoints);
    SDL_BlitSurface(Charger->ImageMorpion[Variable_Pour_Image], NULL, SDL_GetVideoSurface(), &Charger->positionImageMorpion);

    /*On place les images à 35 pixels de distance après avoir blitté les images (pour pouvoir blitter pas dessus)*/
    for(i=0; i<pointJoueur1; i++)
    {
        Charger->positionPointsCroix.x=(10+i*35)+260;
        SDL_BlitSurface(Charger->PointsCroix, NULL, SDL_GetVideoSurface(), &Charger->positionPointsCroix);
    }
    for(i=0; i<pointJoueur2; i++)
    {
        Charger->positionPointsRond.x=(10+i*35)+260;
        SDL_BlitSurface(Charger->PointsRond, NULL, SDL_GetVideoSurface(), &Charger->positionPointsRond);
    }
}
void evenement_Click3( SDL_Event event,Pions* TourJoueur,ComposantsFonctionPourJeu Charger,int terrain[][9],int*coups,SDL_Surface **Curseur,int*Variable_Pour_Image )
{
    if( event.button.button == SDL_BUTTON_LEFT && event.button.x<=859 && event.button.y<=485)
    {
        if (collision(event.button.x, event.button.y, Charger.position_Grille))
        {
            if( *TourJoueur == CROIX )
            {
                if (terrain[(event.button.x -265)/ 66][(event.button.y -35)/ 50]==VIDE)/*Si la case est vide*/
                {
                    Mix_PlayChannel(1, Mix_GetChunk(0) , 0);
                    terrain[(event.button.x -265)/ 66][(event.button.y -35)/ 50]= CROIX;/*on attribut Croix à la case*/
                    *TourJoueur = ROND;/*on change de joueur*/
                    (*coups)--;
                    SDL_FreeSurface(*Curseur);
                    *Curseur= SDL_LoadBMP("images/petitRond.bmp");
                }
            }
            else
            {
                if (terrain[(event.button.x -265)/ 66][(event.button.y -35)/ 50]==VIDE)/*Si la case est vide*/
                {
                    Mix_PlayChannel(1, Mix_GetChunk(0), 0);
                    terrain[(event.button.x -265)/ 66][(event.button.y -35)/ 50]= ROND;/*on attribut ROND à la case*/
                    *TourJoueur = CROIX;
                    (*coups)--;
                    SDL_FreeSurface(*Curseur);
                    *Curseur= SDL_LoadBMP("images/petiteCroix.bmp");
                }
            }
        }
        (*Variable_Pour_Image)++;/*l'anim change à chaque clic*/
        if (*Variable_Pour_Image==3)
        {
            *Variable_Pour_Image=0;
        }
    }
}
void libererJeu3(ComposantsFonctionPourJeu* Charger)
{
    int i;
    SDL_FreeSurface(Charger->croix);/* on libère le tout*/
    SDL_FreeSurface(Charger->rond);
    SDL_FreeSurface(Charger->PointsCroix);
    SDL_FreeSurface(Charger->PointsRond);
    SDL_FreeSurface(Charger->grille);
    SDL_FreeSurface(Charger->TextePoints);
    SDL_FreeSurface(Charger->Quitter);
    TTF_CloseFont(Charger->police);
    for (i=0; i<9; i++)
    {
        SDL_FreeSurface(Charger->ImageMorpion[i]);
    }
}
void Jeu3()
{
    SDL_Event event;
    SDL_Surface *Curseur=SDL_LoadBMP("images/petiteCroix.bmp");;
    SDL_Rect positionCurseur;

    int recommencer=1;/* Pour le grand do while*/
    int pointJoueur1=0, pointJoueur2=0;
    int gagnant;
    int VariablePourSon=0;
    int Bloquer_Affichage_Son=1;

    ComposantsFonctionPourJeu Charger;
    Composants_Pour_FonctionPourJeu3(&Charger);
    do
    {
        int terrain[9][9] = {{0}};/*On réinitialise les valeurs*/
        int continuer = 1;
        int coups =81;
        int Variable_Pour_Image=0;
        Pions TourJoueur = CROIX;/*Les croix Commencent*/
        /*Un premier blit pour une belle présentation*/
        Blits3(terrain, Variable_Pour_Image , pointJoueur1, pointJoueur2 ,&Charger);

        while (continuer && coups >0)
        {
            SDL_WaitEvent(&event);
            switch( event.type )
            {
            case SDL_MOUSEMOTION:
                Bloquer_Affichage_Son=1;
                /*if (collision(event.button.x,event.button.y, Charger.pos_Quitter ))
                {
                    SDL_FreeSurface(Curseur);
                }*/
                break;
            case SDL_QUIT:
                SDL_FreeSurface(Curseur);
                libererJeu3(&Charger);
                exit(0);
                break;
            case SDL_MOUSEBUTTONUP:
                evenement_Click3(event,&TourJoueur,Charger,terrain,&coups,&Curseur,&Variable_Pour_Image);
                if (collision(event.button.x,event.button.y, Charger.pos_Quitter ))
                {
                    continuer=0;
                    libererJeu1(&Charger);
                    Choix();
                }
                break;
            case SDL_KEYDOWN: /* Si appui d'une touche */
                switch (event.key.keysym.sym)
                {
                case SDLK_s:
                    Blits3(terrain, Variable_Pour_Image , pointJoueur1, pointJoueur2 ,&Charger);
                    ModifierSon (&VariablePourSon);
                    Bloquer_Affichage_Son=0;
                    break;
                case SDLK_ESCAPE:
                    continuer=0;
                    SDL_FreeSurface(Curseur);
                    libererJeu3(&Charger);
                    MenuPrincipal();
                    break;
                default:
                    break;
                }
                break;
            }
            if (Bloquer_Affichage_Son==1)
            {
                /*On vérifie si la partie est finie*/
                VerifierFinMatch3(terrain,&pointJoueur1,&pointJoueur2, &continuer , &gagnant );
                Blits3(terrain, Variable_Pour_Image , pointJoueur1, pointJoueur2 ,&Charger);
                /*après tout ça on blit le curseur*/
                positionCurseur.x = event.motion.x-(Curseur->w / 2);
                positionCurseur.y = event.motion.y-(Curseur->h / 2);
                SDL_BlitSurface(Curseur, NULL, SDL_GetVideoSurface(), &positionCurseur);
                SDL_Flip(SDL_GetVideoSurface());
            }
        }
        SDL_Delay(500);/*On patiente pour que l'utilisateur voie ou l'adversaire à joué*/
        FinMatch(&recommencer, &gagnant);/*Affichage gagné/ perdu/ MatchNull */
        SDL_Flip(SDL_GetVideoSurface());
        Curseur=SDL_LoadBMP("images/petiteCroix.bmp");
    }
    while (recommencer);
    SDL_FreeSurface(Curseur);
    libererJeu3(&Charger);
}
void VerifierFinMatch3(int terrain [][9],int *pointJoueur1,int *pointJoueur2 ,int *continuer, int *gagnant)
{
    int i,j,k,l,m,n,o;
        n=*pointJoueur1;
        o=*pointJoueur2;
    for (i=0;i<9;i++)
    {
        for(j=0;j<5;j++)
        {
            if((terrain [i][j]== CROIX && terrain [i][j+1]== CROIX && terrain [i][j+2]== CROIX && terrain [i][j+3]== CROIX && terrain [i][j+4]== CROIX )||
                (terrain [j][i]== CROIX && terrain [j+1][i]== CROIX && terrain [j+2][i]== CROIX && terrain [j+3][i]== CROIX && terrain [j+4][i]== CROIX ))
            {
                *pointJoueur1+=1;
                *continuer=0;
                *gagnant=Joueur1;
            }
        }
    }
    for(m=0;m<5;m++)
    {
        if((terrain [m][m]== CROIX && terrain [m+1][m+1]== CROIX && terrain [m+2][m+2]== CROIX && terrain [m+3][m+3]== CROIX && terrain [m+4][m+4]== CROIX )||
            (terrain [m][8-m]== CROIX && terrain [m+1][7-m]== CROIX && terrain [m+2][6-m]== CROIX && terrain [m+3][5-m]== CROIX && terrain [m+4][4-m]== CROIX ))
        {
            *pointJoueur1+=1;
            *continuer=0;
            *gagnant=Joueur1;
        }
    }
    for (k=0;k<4;k++)
    {
         if((terrain [k][k+1]== CROIX && terrain [k+1][k+2]== CROIX && terrain [k+2][k+3]== CROIX && terrain [k+3][k+4]== CROIX && terrain [k+4][k+5]== CROIX )||
            (terrain [k+1][k]== CROIX && terrain [k+2][k+1]== CROIX && terrain [k+3][k+2]== CROIX && terrain [k+4][k+3]== CROIX && terrain [k+5][k+4]== CROIX )||
            (terrain [k][7-k]== CROIX && terrain [k+1][6-k]== CROIX && terrain [k+2][5-k]== CROIX && terrain [k+3][4-k]== CROIX && terrain [k+4][3-k]== CROIX )||
            (terrain [k+1][8-k]== CROIX && terrain [k+2][7-k]== CROIX && terrain [k+3][6-k]== CROIX && terrain [k+4][5-k]== CROIX && terrain [k+5][4-k]== CROIX ))
        {
            *pointJoueur1+=1;
            *continuer=0;
            *gagnant=Joueur1;
        }
    }
    for (l=0;l<3;l++)
    {
         if((terrain [l][l+2]== CROIX && terrain [l+1][l+3]== CROIX && terrain [l+2][l+4]== CROIX && terrain [l+3][l+5]== CROIX && terrain [l+4][l+6]== CROIX )||
            (terrain [l+2][l]== CROIX && terrain [l+3][l+1]== CROIX && terrain [l+4][l+2]== CROIX && terrain [l+5][l+3]== CROIX && terrain [l+6][l+4]== CROIX )||
            (terrain [l][6-l]== CROIX && terrain [l+1][5-l]== CROIX && terrain [l+2][4-l]== CROIX && terrain [l+3][3-l]== CROIX && terrain [l+4][2-l]== CROIX )||
            (terrain [l+2][8-l]== CROIX && terrain [l+3][7-l]== CROIX && terrain [l+4][6-l]== CROIX && terrain [l+5][5-l]== CROIX && terrain [l+6][4-l]== CROIX ))
        {
            *pointJoueur1+=1;
            *continuer=0;
            *gagnant=Joueur1;
        }
    }
    for (m=0;m<2;m++)
    {
         if((terrain [m][m+3]== CROIX && terrain [m+1][m+4]== CROIX && terrain [m+2][m+5]== CROIX && terrain [m+3][m+6]== CROIX && terrain [m+4][m+7]== CROIX )||
            (terrain [m+3][m]== CROIX && terrain [m+4][m+1]== CROIX && terrain [m+5][m+2]== CROIX && terrain [m+6][m+3]== CROIX && terrain [m+7][m+4]== CROIX )||
            (terrain [m][5-m]== CROIX && terrain [m+1][4-m]== CROIX && terrain [m+2][3-m]== CROIX && terrain [m+3][2-m]== CROIX && terrain [m+4][1-m]== CROIX )||
            (terrain [m+3][8-m]== CROIX && terrain [m+4][7-m]== CROIX && terrain [m+5][6-m]== CROIX && terrain [m+6][5-m]== CROIX && terrain [m+7][4-m]== CROIX ))
        {
            *pointJoueur1+=1;
            *continuer=0;
            *gagnant=Joueur1;
        }
    }
    if((terrain [4][0]== CROIX && terrain [3][1]== CROIX && terrain [2][2]== CROIX && terrain [1][3]== CROIX && terrain [0][4]== CROIX )||
        (terrain [0][4]== CROIX && terrain [1][5]== CROIX && terrain [2][6]== CROIX && terrain [3][7]== CROIX && terrain [4][8]== CROIX )||
        (terrain [4][8]== CROIX && terrain [5][7]== CROIX && terrain [6][6]== CROIX && terrain [7][5]== CROIX && terrain [8][4]== CROIX )||
        (terrain [8][4]== CROIX && terrain [7][3]== CROIX && terrain [6][2]== CROIX && terrain [5][1]== CROIX && terrain [4][0]== CROIX ))
    {
        *pointJoueur1+=1;
        *continuer=0;
        *gagnant=Joueur1;
    }
    for (i=0;i<9;i++)
    {
        for(j=0;j<5;j++)
        {
            if((terrain [i][j]== ROND && terrain [i][j+1]== ROND && terrain [i][j+2]== ROND && terrain [i][j+3]== ROND && terrain [i][j+4]== ROND )||
                (terrain [j][i]== ROND && terrain [j+1][i]== ROND && terrain [j+2][i]== ROND && terrain [j+3][i]== ROND && terrain [j+4][i]== ROND ))
            {
                *pointJoueur2+=1;
                *continuer=0;
                *gagnant=Joueur2;
            }
        }
    }
    for(m=0;m<5;m++)
    {
        if((terrain [m][m]== ROND && terrain [m+1][m+1]== ROND && terrain [m+2][m+2]== ROND && terrain [m+3][m+3]== ROND && terrain [m+4][m+4]== ROND )||
            (terrain [m][8-m]== ROND && terrain [m+1][7-m]== ROND && terrain [m+2][6-m]== ROND && terrain [m+3][5-m]== ROND && terrain [m+4][4-m]== ROND ))
        {
            *pointJoueur2+=1;
            *continuer=0;
            *gagnant=Joueur2;
        }
    }
    for (k=0;k<4;k++)
    {
         if((terrain [k][k+1]== ROND && terrain [k+1][k+2]== ROND && terrain [k+2][k+3]== ROND && terrain [k+3][k+4]== ROND && terrain [k+4][k+5]== ROND )||
            (terrain [k+1][k]== ROND && terrain [k+2][k+1]== ROND && terrain [k+3][k+2]== ROND && terrain [k+4][k+3]== ROND && terrain [k+5][k+4]== ROND )||
            (terrain [k][7-k]== ROND && terrain [k+1][6-k]== ROND && terrain [k+2][5-k]== ROND && terrain [k+3][4-k]== ROND && terrain [k+4][3-k]== ROND )||
            (terrain [k+1][8-k]== ROND && terrain [k+2][7-k]== ROND && terrain [k+3][6-k]== ROND && terrain [k+4][5-k]== ROND && terrain [k+5][4-k]== ROND ))
        {
            *pointJoueur2+=1;
            *continuer=0;
            *gagnant=Joueur2;
        }
    }
    for (l=0;l<3;l++)
    {
         if((terrain [l][l+2]== ROND && terrain [l+1][l+3]== ROND && terrain [l+2][l+4]== ROND && terrain [l+3][l+5]== ROND && terrain [l+4][l+6]== ROND )||
            (terrain [l+2][l]== ROND && terrain [l+3][l+1]== ROND && terrain [l+4][l+2]== ROND && terrain [l+5][l+3]== ROND && terrain [l+6][l+4]== ROND )||
            (terrain [l][6-l]== ROND && terrain [l+1][5-l]== ROND && terrain [l+2][4-l]== ROND && terrain [l+3][3-l]== ROND && terrain [l+4][2-l]== ROND )||
            (terrain [l+2][8-l]== ROND && terrain [l+3][7-l]== ROND && terrain [l+4][6-l]== ROND && terrain [l+5][5-l]== ROND && terrain [l+6][4-l]== ROND ))
        {
            *pointJoueur2+=1;
            *continuer=0;
            *gagnant=Joueur2;
        }
    }
    for (m=0;m<2;m++)
    {
         if((terrain [m][m+3]== ROND && terrain [m+1][m+4]== ROND && terrain [m+2][m+5]== ROND && terrain [m+3][m+6]== ROND && terrain [m+4][m+7]== ROND )||
            (terrain [m+3][m]== ROND && terrain [m+4][m+1]== ROND && terrain [m+5][m+2]== ROND && terrain [m+6][m+3]== ROND && terrain [m+7][m+4]== ROND )||
            (terrain [m][5-m]== ROND && terrain [m+1][4-m]== ROND && terrain [m+2][3-m]== ROND && terrain [m+3][2-m]== ROND && terrain [m+4][1-m]== ROND )||
            (terrain [m+3][8-m]== ROND && terrain [m+4][7-m]== ROND && terrain [m+5][6-m]== ROND && terrain [m+6][5-m]== ROND && terrain [m+7][4-m]== ROND ))
        {
            *pointJoueur2+=1;
            *continuer=0;
            *gagnant=Joueur2;
        }
    }
    if((terrain [4][0]== ROND && terrain [3][1]== ROND && terrain [2][2]== ROND && terrain [1][3]== ROND && terrain [0][4]== ROND )||
        (terrain [0][4]== ROND && terrain [1][5]== ROND && terrain [2][6]== ROND && terrain [3][7]== ROND && terrain [4][8]== ROND )||
        (terrain [4][8]== ROND && terrain [5][7]== ROND && terrain [6][6]== ROND && terrain [7][5]== ROND && terrain [8][4]== ROND )||
        (terrain [8][4]== ROND && terrain [7][3]== ROND && terrain [6][2]== ROND && terrain [5][1]== ROND && terrain [4][0]== ROND ))
    {
        *pointJoueur2+=1;
        *continuer=0;
        *gagnant=Joueur2;
    }
    if((*gagnant!=Joueur2)&&(*gagnant!=Joueur1))
    {
        *gagnant=MatchNull;
    }
        if (*pointJoueur1>n)
        *pointJoueur1=n+1;
        if (*pointJoueur2>o)
        *pointJoueur2=o+1;
}
