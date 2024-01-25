#include "graphics.h"

SDL_Renderer *renderer = NULL;
SDL_Window *fenetre = NULL;
int screenWidth, screenHeight;
int alienWidth, alienHeight;

int windowsConfig(int * screenWidth, int * screenHeight, int * alienWidth, int * alienHeight) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    fscanf(configFile, "SCREEN_WIDTH=%d \n", screenWidth);
    fscanf(configFile, "SCREEN_HEIGHT=%d \n", screenHeight);
    fscanf(configFile, "ALIEN_WIDTH=%d \n", alienWidth);
    fscanf(configFile, "ALIEN_HEIGHT=%d \n", alienHeight);

    fclose(configFile);
    return 0;
}

void initSDL() {
    windowsConfig(&screenWidth, &screenHeight, &alienWidth, &alienHeight);

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
    SDL_Rect rectangle = {alien->x, alien->y, alienWidth, alienHeight};
    SDL_RenderFillRect(renderer, &rectangle);
}

void mettreAJourAffichageMenu() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Affichage des boutons
    int largeurBouton = 200;
    int hauteurBouton = 50;
    int espacementBouton = 20;
    int xBouton = (screenWidth - largeurBouton) / 2;
    int yBouton = (screenHeight - (3 * hauteurBouton + 2 * espacementBouton)) / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Bouton "Continue"
    SDL_Rect rectContinue = {xBouton, yBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectContinue);
    //dessinerTexte("Continue", xBouton + 20, yBouton + 10, 20);

    // Bouton "Quit"
    SDL_Rect rectQuit = {xBouton, yBouton + hauteurBouton + espacementBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectQuit);
    //dessinerTexte("Quit", xBouton + 20, yBouton + hauteurBouton + espacementBouton + 10, 20);

    // Bouton "Sauvegarder"
    SDL_Rect rectSauvegarder = {xBouton, yBouton + 2 * (hauteurBouton + espacementBouton), largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectSauvegarder);
    //dessinerTexte("Sauvegarder", xBouton + 20, yBouton + 2 * (hauteurBouton + espacementBouton) + 10, 20);

    SDL_RenderPresent(renderer);
}

/*
void dessinerTexte(const char *texte, int x, int y, int taillePolice) {

    
    TTF_Font *police = TTF_OpenFont("vendor/font/Alien_Moon.ttf", taillePolice);
    if (police == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return;
    }

    SDL_Color couleurTexte = {0, 0, 0, 255}; // Couleur du texte en noir
    SDL_Surface *surfaceTexte = TTF_RenderText_Solid(police, texte, couleurTexte);
    if (surfaceTexte == NULL) {
        fprintf(stderr, "Erreur lors de la création de la surface texte : %s\n", TTF_GetError());
        TTF_CloseFont(police);
        return;
    }

    SDL_Texture *textureTexte = SDL_CreateTextureFromSurface(renderer, surfaceTexte);
    if (textureTexte == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture texte : %s\n", SDL_GetError());
        SDL_FreeSurface(surfaceTexte);
        TTF_CloseFont(police);
        return;
    }
    
    
    SDL_Rect destRect = {x, y, surfaceTexte->w, surfaceTexte->h};
    SDL_RenderCopy(renderer, textureTexte, NULL, &destRect);

    SDL_DestroyTexture(textureTexte);
    SDL_FreeSurface(surfaceTexte);
    TTF_CloseFont(police);

    
}
*/
