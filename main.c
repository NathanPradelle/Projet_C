#include "graphics.h"
#include "alien.h"
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int delay = 100;
    int result = initSDL_main(argc, argv);

    if (result != 0) {
        return result;
    }

    Alien *listeAliens = NULL;
    int numberOfAliens = 0;
    Alien *courant = NULL;

    SDL_Event event;
    int continuer = 1;

    ajouterAlien(&listeAliens, &numberOfAliens);

    while (continuer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                continuer = 0;
            }
        }
        Alien *courant = listeAliens;
        Uint32 tempsEcoule = SDL_GetTicks();
        int tempsint = (int)tempsEcoule;

        if (tempsint % 1000 < delay){
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

        
        detecterCollisions(listeAliens);

        mettreAJourAffichage();
        SDL_Delay(delay);

        while (courant != NULL) {
            Alien *suivant = courant->next;
            detruireAlien(courant);
            courant = suivant;
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
