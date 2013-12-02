#include <stdlib.h>
#include <SDL/SDL.h>
#include<SDL/SDL_ttf.h>
typedef enum Pions Pions;
enum {MatchNull,Joueur1,Joueur2};
enum Pions
{
    VIDE,CROIX, ROND
};
typedef struct
{
    SDL_Surface *croix;
    SDL_Surface *rond;
    SDL_Surface *PointsCroix;
    SDL_Surface *PointsRond;
    SDL_Surface *grille;
    SDL_Surface *TextePoints;
    SDL_Surface *ImageMorpion[3];
    SDL_Surface *Quitter;
    //SDL_Surface *img=NULL;

    SDL_Rect positionPointsCroix;
    SDL_Rect positionPointsRond;
    SDL_Rect position_Grille;
    SDL_Rect positionImageMorpion;
    SDL_Rect positionImagePoints;
    SDL_Rect position ;
    SDL_Rect pos_Quitter;
    //SDL_Rect pos_img;
    TTF_Font *police ;

}ComposantsFonctionPourJeu;
void FinMatch(int *recommencer, int *gagnant );
void Composants_Pour_FonctionPourJeu1(ComposantsFonctionPourJeu *Composants_Pour_FonctionPourJeu);
void VerifierFinMatch1(int terrain [][3],int *pointJoueur1,int *pointJoueur2 ,int *continuer, int *gagnant );
void Blits1( int terrain[][3], int t , int pointJoueur1, int pointJoueur2 ,ComposantsFonctionPourJeu* Charger);
void evenement_Click1( SDL_Event event,Pions* TourJoueur,ComposantsFonctionPourJeu Charger,int terrain[][3],int*coups,SDL_Surface **Curseur,int*t );
void libererJeu1(ComposantsFonctionPourJeu* Charger);
void Jeu1();

void Composants_Pour_FonctionPourJeu2(ComposantsFonctionPourJeu *Composants_Pour_FonctionPourJeu);
void VerifierFinMatch2(int terrain [][6],int *pointJoueur1,int *pointJoueur2 ,int *continuer, int *gagnant );
void Blits2( int terrain[][6], int t , int pointJoueur1, int pointJoueur2 ,ComposantsFonctionPourJeu* Charger);
void evenement_Click2( SDL_Event event,Pions* TourJoueur,ComposantsFonctionPourJeu Charger,int terrain[][6],int*coups,SDL_Surface **Curseur,int*t );
void libererJeu2(ComposantsFonctionPourJeu* Charger);
void Jeu2();

void Composants_Pour_FonctionPourJeu3(ComposantsFonctionPourJeu *Composants_Pour_FonctionPourJeu);
void VerifierFinMatch3(int terrain [][9],int *pointJoueur1,int *pointJoueur2 ,int *continuer, int *gagnant );
void Blits3( int terrain[][9], int t , int pointJoueur1, int pointJoueur2 ,ComposantsFonctionPourJeu* Charger);
void evenement_Click3( SDL_Event event,Pions* TourJoueur,ComposantsFonctionPourJeu Charger,int terrain[][9],int*coups,SDL_Surface **Curseur,int*t );
void libererJeu3(ComposantsFonctionPourJeu* Charger);
void Jeu3();
