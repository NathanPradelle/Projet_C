#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL_ttf.h>
#include <SDL.h>
#include "alien.h"

extern SDL_Renderer *renderer;
extern SDL_Window *fenetre;
extern Alien *listeAliens;
extern int screenWidth;
extern int screenHeight;
extern int alienWidth;
extern int alienHeight;
extern int menuActif;
extern SDL_Texture *textureMenu;
extern SDL_Rect positionMenu;
extern int largeurBouton;
extern int hauteurBouton;
extern int espacementBouton;
extern int xBouton;
extern int yBouton;

void initSDL();
int initSDL_main(int argc, char *argv[]);
void cleanupSDL();
void effacerFenetre();
void mettreAJourAffichage();
void detecterCollisions(Alien *listeAliens);
void dessinerAlien(const Alien *alien);
void mettreAJourAffichageMenu();
void dessinerTexte(const char *texte, int x, int y, int taillePolice);
void actionBoutonSauvegarder(const char *nomFichier, Alien *listeAliens);
void chargerListeDepuisFichier(const char *nomFichier, Alien **listeAliens, int *numberOfAliens);

#endif
