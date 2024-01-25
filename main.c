#include "graphics.h"
#include "alien.h"
#include <time.h>

int main(int argc, char *argv[]) {
    
    srand(time(NULL));
    int delay = 0;
    int result = initSDL_main(argc, argv);

    if (result != 0) {
        return result;
    }

    Alien *listeAliens = NULL;
    int numberOfAliens = 0;
    Alien *courant = NULL;

    SDL_Event event;
    int menuActif = 0;
    int continuer = 1;

    ajouterAlien(&listeAliens, &numberOfAliens);


    while (continuer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
            continuer = 0;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                menuActif = !menuActif;
            }
        } else if (menuActif && event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if (mouseX >= xBouton && mouseX <= xBouton + largeurBouton &&
                mouseY >= yBouton && mouseY <= yBouton + hauteurBouton) {
                menuActif = !menuActif; // Désactive le menu
            }

            // Bouton "Quit"
            if (mouseX >= xBouton && mouseX <= xBouton + largeurBouton &&
                mouseY >= yBouton + hauteurBouton + espacementBouton &&
                mouseY <= yBouton + 2 * (hauteurBouton + espacementBouton)) {
                continuer = 0; // Quitte l'application
            }

        }
        
        if (!menuActif) {

            Alien *courant = listeAliens;
            Uint32 tempsEcoule = SDL_GetTicks();
            int tempsint = (int)tempsEcoule;

            if (tempsint % 1000 == 0){
                ajouterAlien(&listeAliens, &numberOfAliens);
            }

            
            while (courant != NULL) {
                deplacerAlien(courant);
                courant = courant->next;
            }

            effacerFenetre();

            courant = listeAliens;

            while (courant != NULL) {
                dessinerAlien(courant);
                courant = courant->next;
            }
            
            mettreAJourAffichage();
            SDL_Delay(delay);
        }

        else {
            
            mettreAJourAffichageMenu();

        }
    }

    courant = listeAliens;

    while (courant != NULL) {
            Alien *suivant = courant->next;
            detruireAlien(courant);
            courant = suivant;
    }

    cleanupSDL();

    return 0;
}