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
    
    int tempsint = 0;
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
            effacerFenetre();
            Alien *courant = listeAliens;
            tempsint++;

            if (tempsint > 500){
                ajouterAlien(&listeAliens, &numberOfAliens);
                tempsint = 0;
            }

            while (courant != NULL) {
                deplacerAlien(courant);
                courant = courant->next;
            }

            courant = listeAliens;

            while (courant != NULL) {
                dessinerAlien(courant);
                courant = courant->next;
            }
            
            detecterCollisions(listeAliens);

            while (courant != NULL) {
                Alien *suivant = courant->next;
                detruireAlien(courant);
                courant = suivant;
            }
            mettreAJourAffichage();
            SDL_Delay(delay);
        } else {
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