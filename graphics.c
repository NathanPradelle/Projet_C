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

void dessinerAlien(const Alien *alien) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rectangle = {alien->x, alien->y, 15, 15};
    SDL_RenderFillRect(renderer, &rectangle);
}