#include "graphics.h"

SDL_Renderer *renderer = NULL;
SDL_Window *fenetre = NULL;

int windowsConfig(int * screenWidth, int * screenHeight) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    fscanf(configFile, "SCREEN_WIDTH=%d \n", screenWidth);
    fscanf(configFile, "SCREEN_HEIGHT=%d \n", screenHeight);

    fclose(configFile);
    return 0;
}

void initSDL() {
    int screenWidth, screenHeight;
    windowsConfig(&screenWidth, &screenHeight);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {

        exit(1);
    }

    fenetre = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (fenetre == NULL) {
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        exit(1);
    }
}

int initSDL_main(int argc, char *argv[]) {
    initSDL();
    return 0;
}

void cleanupSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}

void effacerFenetre() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void mettreAJourAffichage() {
    SDL_RenderPresent(renderer);
}

void detecterCollisions(Alien *listeAliens) {
    Alien *alien1 = listeAliens;

    while (alien1 != NULL) {
        Alien *alien2 = alien1->next;

        while (alien2 != NULL) {
            if (alien1->x < alien2->x + 15 &&
                alien1->x + 15 > alien2->x &&
                alien1->y < alien2->y + 15 &&
                alien1->y + 15 > alien2->y) {
                // printf("Collision détectée entre deux aliens!\n");
                if(alien1->type!=alien2->type && alien1->alive && alien2->alive){
                    if(alien1->type==0){
                        if(alien2->type==1){
                            alien1->alive=0;
                        } else {
                            alien2->alive=0;
                        }
                    }
                    if(alien1->type==1){
                        if(alien2==0){
                            alien2->alive=0;
                        } else {
                            alien1->alive=0;
                        }
                    }
                    if(alien1->type==2){
                        if(alien2->type==0){
                            alien1->alive=0;
                        } else {
                            alien2->alive=0;
                        }
                    }
                }
            }

            alien2 = alien2->next;
        }

        alien1 = alien1->next;
    }
}

void dessinerAlien(const Alien *alien) {
    if(alien->alive==0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    } else {
        if(alien->type==0){
            SDL_SetRenderDrawColor(renderer, 255, 255-alien->day, 255-alien->day, 255-alien->day);
        }
        if(alien->type==1){
            SDL_SetRenderDrawColor(renderer, 255-alien->day, 255, 255-alien->day, 255-alien->day);
        }
        if(alien->type==2){
            SDL_SetRenderDrawColor(renderer, 255-alien->day, 255-alien->day, 255, 255-alien->day);
        }
    }
    SDL_Rect rectangle = {alien->x, alien->y, 15, 15};
    SDL_RenderFillRect(renderer, &rectangle);
}