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
            switch (event.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_MOUSEMOTION:
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                    menuActif = !menuActif;}
                    break;
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