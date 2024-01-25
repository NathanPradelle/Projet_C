#include "graphics.h"
#include "alien.h"
<<<<<<< HEAD

int main(int argc, char *argv[]) {
=======
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));

>>>>>>> 3c6f99c5a8d3e0f7d9d2506a3cb8863a3ce3d3d1
    int result = initSDL_main(argc, argv);

    if (result != 0) {
        return result;
    }

    Alien *listeAliens = NULL;
<<<<<<< HEAD
=======
    int numberOfAliens = 0;
>>>>>>> 3c6f99c5a8d3e0f7d9d2506a3cb8863a3ce3d3d1
    Alien *courant = NULL;

    SDL_Event event;
    int continuer = 1;

    while (continuer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                continuer = 0;
            }
        }

<<<<<<< HEAD
        ajouterAlien(&listeAliens);
    

        Alien *courant = listeAliens;

=======
        Alien *courant = listeAliens;

        ajouterAlien(&listeAliens, &numberOfAliens);

>>>>>>> 3c6f99c5a8d3e0f7d9d2506a3cb8863a3ce3d3d1
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
        SDL_Delay(100);
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
