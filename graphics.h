#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include "alien.h"

extern SDL_Renderer *renderer;
extern SDL_Window *fenetre;
extern Alien *listeAliens;
extern int screenWidth;
extern int screenHeight;
extern int alienWidth;
extern int alienHeight;

void initSDL();
int initSDL_main(int argc, char *argv[]);
void cleanupSDL();
void effacerFenetre();
void mettreAJourAffichage();
void dessinerAlien(const Alien *alien);

#endif
