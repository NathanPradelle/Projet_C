#include "graphics.h"
#include "alien.h"
#include <time.h>

int refreshDelay = 0;
int maxAliens = 20;

int globalConfig(int *refreshDelay, int *maxAliens) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    char line[150];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        sscanf(line, "REFRESH_DELAY=%d", refreshDelay);
        sscanf(line, "MAX_ALIEN=%d", maxAliens);
    }

    fclose(configFile);
    return 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    globalConfig(&refreshDelay, &maxAliens);

    int result = initSDL_main(argc, argv);
    if (result != 0) {
        return result;
    }
    
    int xBouton = (screenWidth - largeurBouton) / 2;
    int yBouton = (screenHeight - (3 * hauteurBouton + 2 * espacementBouton)) / 2;

    Alien *listeAliens = NULL;
    int numberOfAliens = 0;
    Alien *courant = NULL;

    SDL_Event event;
    int menuActif = 0;
    int continuer = 1;

    while (numberOfAliens < maxAliens) {
        ajouterAlien(&listeAliens, &numberOfAliens);
    }
    
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

                if (mouseX >= xBouton && mouseX <= xBouton + largeurBouton &&
                    mouseY >= yBouton + 2 * (hauteurBouton + espacementBouton) &&
                    mouseY <= yBouton + 3 * (hauteurBouton + espacementBouton)) {
                    actionBoutonSauvegarder("sauvegarde_1.txt", listeAliens);
                }

                if (mouseX >= xBouton && mouseX <= xBouton + largeurBouton &&
                    mouseY >= yBouton + 3 * (hauteurBouton + espacementBouton) &&
                    mouseY <= yBouton + 4 * (hauteurBouton + espacementBouton)) {
                    chargerListeDepuisFichier("sauvegarde_1.txt", &listeAliens, &numberOfAliens);
                }
            }
        }

        if (!menuActif) {
            effacerFenetre();
            Alien *courant = listeAliens;
            tempsint++;

            while (courant != NULL) {
                deplacerAlien(courant);
                courant = courant->next;
            }

            courant = listeAliens;
            detecterCollisions(listeAliens);

            while (courant != NULL) {
                dessinerAlien(courant);
                courant = courant->next;
            }
            
            while (courant != NULL) {
                Alien *suivant = courant->next;
                detruireAlien(courant);
                courant = suivant;
            }
            mettreAJourAffichage();
            SDL_Delay(refreshDelay);
        } else {
            mettreAJourAffichageMenu(xBouton, yBouton);
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