#include <stdlib.h>
#include "vendor/include/SDL.h"
#include "vendor/include/SDL_image.h"
#include "vendor/include/SDL_ttf.h"
#include "vendor/include/SDL_mixer.h"
#include "main.h"
#include "graphics.h"
#include "alien.h"
#include <time.h>

#define MAX_ALIENS 50

#define MENU_SIZE 4

char *fichier_actuel;
Alien *listeAliens = NULL;
int numberOfAliens = 0;

int main(int argc, char *argv[]) {
    ProgramState state = MENU;

    while (state != QUIT) {
        switch (state) {
            case MENU:
                state = runMenu();
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
                }
                Mix_Music *music = Mix_LoadMUS("music/Program in C.mp3");
                if (!music) {
                    printf("Erreur lors du chargement du fichier MP3: %s\n", Mix_GetError());
                    return QUIT;
                }
                if (Mix_PlayMusic(music, 1) < 0) {
                    printf("Erreur lors de la lecture de la musique: %s\n", Mix_GetError());
                    return QUIT;
                }
                Mix_RewindMusic();
                break;
            case SIMULATION:
                state = runSimulation();
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
                }
                if (!music) {
                    printf("Erreur lors du chargement du fichier MP3: %s\n", Mix_GetError());
                    return QUIT;
                }
                if (Mix_PlayMusic(music, 1) < 0) {
                    printf("Erreur lors de la lecture de la musique: %s\n", Mix_GetError());
                    return QUIT;
                }
                break;
            case QUIT:
                return QUIT;
                break;
        break;
        }
    }

    return 0;
}

ProgramState runMenu() { 

    int result = initSDL_main();
    if (result != 0) {
        return QUIT;
    }

    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return QUIT;
    }

    TTF_Font *font = TTF_OpenFont("vendor/font/Alien_Moon.ttf", 20);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        SDL_Delay(2000);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return QUIT;
    }

    SDL_Color textColor = {255, 255, 255, 0};

    char *menuOptions[MENU_SIZE] = {"commencer", "modifier", "sauvgardes", "quitter"};
    int selectedOption = 0;

    SDL_Texture *optionTextures[MENU_SIZE];

    SDL_Event event;
    int running = 1;
    int sauvegardeActif = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        selectedOption = (selectedOption - 1 + MENU_SIZE) % MENU_SIZE;
                        break;
                    case SDLK_DOWN:
                        selectedOption = (selectedOption + 1) % MENU_SIZE;
                        break;
                    case SDLK_RETURN:
                        if (selectedOption == 0) {
                            return SIMULATION;
                        }
                        if (selectedOption == 1) {
                            
                        }
                        if (selectedOption == 2) {
                            sauvegardeActif = !sauvegardeActif;
                        }
                        if (selectedOption == 4) {
                            running = 0;
                        }
                        break;
                }
            }
            else if (sauvegardeActif && event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            int xBouton = (screenWidth - (3 * largeurBouton + 2 * espacementBouton)) / 2;
            int yBouton = (screenHeight - (4 * hauteurBouton + 2 * espacementBouton)) / 2;

            if (mouseX >= xBouton + largeurBouton + espacementBouton && mouseX <= xBouton + largeurBouton + espacementBouton + largeurBouton &&
                mouseY >= yBouton && mouseY <= yBouton + hauteurBouton){
                viderFichier("sauvegarde_1.txt");
            }
            if (mouseX >= xBouton + largeurBouton + espacementBouton && mouseX <= xBouton + largeurBouton + espacementBouton + largeurBouton &&
                mouseY >= yBouton + hauteurBouton + espacementBouton && mouseY <= yBouton + hauteurBouton + espacementBouton + hauteurBouton){
                viderFichier("sauvegarde2.txt");
            }
            if (mouseX >= xBouton + largeurBouton + espacementBouton && mouseX <= xBouton + largeurBouton + espacementBouton + largeurBouton &&
                mouseY >= yBouton + 2 * (hauteurBouton + espacementBouton) && mouseY <= yBouton + 2 * (hauteurBouton + espacementBouton) + hauteurBouton){
                viderFichier("sauvegarde_3.txt");
            }
            if (mouseX >= xBouton + 2 * (largeurBouton + espacementBouton) && mouseX <= xBouton + 2 * (largeurBouton + espacementBouton) + largeurBouton &&
                mouseY >= yBouton && mouseY <= yBouton + hauteurBouton){
                if(!chargerListeDepuisFichier("sauvegarde_1.txt", &listeAliens, &numberOfAliens)){
                    fprintf(stderr, "Erreur lors du chargement du fichier\n");
                } else {
                free(fichier_actuel);
                fichier_actuel = "sauvegarde_1.txt";
                return SIMULATION;
                }
            }
            if (mouseX >= xBouton + 2 * (largeurBouton + espacementBouton) && mouseX <= xBouton + 2 * (largeurBouton + espacementBouton) + largeurBouton &&
                mouseY >= yBouton + hauteurBouton + espacementBouton && mouseY <= yBouton + hauteurBouton + espacementBouton + hauteurBouton){
                if(!chargerListeDepuisFichier("sauvegarde_2.txt", &listeAliens, &numberOfAliens)){
                    fprintf(stderr, "Erreur lors du chargement du fichier\n");
                } else {
                free(fichier_actuel);
                fichier_actuel = "sauvegarde_2.txt";
                return SIMULATION;
                }
            }
            if (mouseX >= xBouton + 2 * (largeurBouton + espacementBouton) && mouseX <= xBouton + 2 * (largeurBouton + espacementBouton) + largeurBouton &&
                mouseY >= yBouton + 2 * (hauteurBouton + espacementBouton) && mouseY <= yBouton + 2 * (hauteurBouton + espacementBouton) + hauteurBouton){
                if(!chargerListeDepuisFichier("sauvegarde_3.txt", &listeAliens, &numberOfAliens)){
                    fprintf(stderr, "Erreur lors du chargement du fichier\n");
                } else {
                free(fichier_actuel);
                fichier_actuel = "sauvegarde_3.txt";
                return SIMULATION;
                }
            }
            if (mouseX >= xBouton + largeurBouton + espacementBouton && mouseX <= xBouton + largeurBouton + espacementBouton + largeurBouton &&
                mouseY >= yBouton + 3 * (hauteurBouton + espacementBouton) && mouseY <= yBouton + 3 * (hauteurBouton + espacementBouton) + hauteurBouton){
                sauvegardeActif = !sauvegardeActif;
            }
        }

        if(!sauvegardeActif){

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < MENU_SIZE; ++i) {
            SDL_Surface *optionSurface = TTF_RenderText_Solid(font, menuOptions[i], textColor);

            if (optionSurface == NULL) {
                printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
                SDL_Delay(2000);
                for (int j = 0; j < i; ++j) {
                    SDL_DestroyTexture(optionTextures[j]);
                    SDL_FreeSurface(TTF_RenderText_Solid(font, menuOptions[j], textColor));
                }
                TTF_CloseFont(font);
                TTF_Quit();
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(fenetre);
                SDL_Quit();
                return QUIT;
            }

            if (i == selectedOption) {
                SDL_SetSurfaceColorMod(optionSurface, 255, 0, 0); // Rouge
            }

            optionTextures[i] = SDL_CreateTextureFromSurface(renderer, optionSurface);
            SDL_FreeSurface(optionSurface);

            if (optionTextures[i] == NULL) {
                printf("Erreur lors de la création de la texture de texte : %s\n", TTF_GetError());
                SDL_Delay(2000);
                for (int j = 0; j <= i; ++j) {
                    SDL_DestroyTexture(optionTextures[j]);
                    SDL_FreeSurface(TTF_RenderText_Solid(font, menuOptions[j], textColor));
                }
                TTF_CloseFont(font);
                TTF_Quit();
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(fenetre);
                SDL_Quit();
                return QUIT;
            }

            SDL_Rect optionRect = {(screenWidth - optionSurface->w) / 2, (MENU_SIZE * optionSurface->h + (MENU_SIZE - 1) * espacementBouton) / 2 + i * (optionSurface->h + espacementBouton), optionSurface->w, optionSurface->h};

            SDL_RenderCopy(renderer, optionTextures[i], NULL, &optionRect);

            SDL_DestroyTexture(optionTextures[i]);
        }

        SDL_RenderPresent(renderer);

        } else{
            int xBouton = (screenWidth - (3 * largeurBouton + 2 * espacementBouton)) / 2;
            int yBouton = (screenHeight - (4 * hauteurBouton + 2 * espacementBouton)) / 2;
            
            mettreAJourAffichageSauvegarde(xBouton, yBouton);
        }
    }
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return QUIT;
}

ProgramState runSimulation() {
    
    srand(time(NULL));
    int delay = 0;
    
    int xBouton = (screenWidth - largeurBouton) / 2;
    int yBouton = (screenHeight - (3 * hauteurBouton + 2 * espacementBouton)) / 2;

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

            if (mouseX >= xBouton && mouseX <= xBouton + largeurBouton &&
                mouseY >= yBouton + 2 * (hauteurBouton + espacementBouton) &&
                mouseY <= yBouton + 3 * (hauteurBouton + espacementBouton)) {
                    if(!fichier_actuel){
                        char *fichierVide = verifVide();
                        actionBoutonSauvegarder(fichierVide, listeAliens);
                        free(fichierVide);
                    }else {
                        actionBoutonSauvegarder(fichier_actuel, listeAliens);
                        }
            }

        }
        }
        if (!menuActif) {
            effacerFenetre();
            Alien *courant = listeAliens;
            tempsint++;

            // SDL_Color fillColor = {0, 0, 0, 0};
            // SDL_Color borderColor = {255, 255, 255, 255};

            // int rng_x = rand() % 400;
            // int rng_y = rand() % 400;

            // itemGenerer(renderer, rng_x, rng_y, 15, fillColor, borderColor);

            if (numberOfAliens < MAX_ALIENS) {
                if (tempsint > 1000){
                    ajouterAlien(&listeAliens, &numberOfAliens);
                    tempsint = 0;
                }
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

    return MENU;
}