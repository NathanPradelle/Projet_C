#include "graphics.h"
#include "alien.h"

SDL_Renderer *renderer = NULL;
SDL_Window *fenetre = NULL;
int screenWidth, screenHeight = 1000;
int agingRender = 240;
int largeurBouton = 200;
int hauteurBouton = 50;
int espacementBouton = 20;
int xBouton, yBouton;

int windowsConfig(int *screenWidth, int *screenHeight, int *agingRender) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    int newAgingRender = 0;
    char line[150];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        sscanf(line, "SCREEN_WIDTH=%d", screenWidth);
        sscanf(line, "SCREEN_HEIGHT=%d", screenHeight);
        sscanf(line, "AGING_RENDER=%d", &newAgingRender);
    }

    // Check field limit
    if (newAgingRender > 255) {
        *agingRender = newAgingRender;
    }

    fclose(configFile);
    return 0;
}

void initSDL() {
    windowsConfig(&screenWidth, &screenHeight, &agingRender);

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

int initSDL_main() {
    initSDL();
    TTF_Init();
    return 0;
}

void cleanupSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    // SDL_Quit();
}

void effacerFenetre() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void mettreAJourAffichage() {
    SDL_RenderPresent(renderer);
}

void collisionsDamages(Alien *alien1, Alien *alien2) {
    if(alien1->type!=alien2->type){
        if(alien1->type == 0){
            if(alien2->type == 1){
                alien1->alive=0;
            } else {
                alien2->alive=0;
            }
        }
        if(alien1->type == 1){
            if(alien2 == 0){
                alien2->alive=0;
            } else {
                alien1->alive=0;
            }
        }
        if(alien1->type == 2){
            if(alien2->type == 0){
                alien1->alive=0;
            } else {
                alien2->alive=0;
            }
        }
    }
}

void detecterCollisions(Alien *listeAliens) {
    Alien *alien1 = listeAliens;

    while (alien1 != NULL) {
        Alien *alien2 = alien1->next;
        SDL_Rect rectangle1 = {alien1->x, alien1->y, alien1->width, alien1->height};

        while (alien2 != NULL) {
            SDL_Rect rectangle2 = {alien2->x, alien2->y, alien2->width, alien2->height};

            if (SDL_HasIntersection(&rectangle1, &rectangle2) == SDL_TRUE) {
                collisionsDamages(alien1, alien2);
            }
            alien2 = alien2->next;
        }
        alien1 = alien1->next;
    }
}

void itemGenerer(SDL_Renderer* renderer, int x, int y, int size, SDL_Color fillColor, SDL_Color borderColor) {
    // Draw square
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_Rect squareRect = {x, y, size, size};
    SDL_RenderFillRect(renderer, &squareRect);

    // Draw borders
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &squareRect);
}

void dessinerAlien(Alien *alien) {
    if(alien->type==0){
        SDL_SetRenderDrawColor(renderer, 255 - alien->age * agingRender/alien->lifespan, 0, 0, 255-alien->age);
    }
    if(alien->type==1){
        SDL_SetRenderDrawColor(renderer, 0, 255 - alien->age * agingRender/alien->lifespan, 0, 255-alien->age);
    }
    if(alien->type==2){
        SDL_SetRenderDrawColor(renderer, 0, 0, 255 - alien->age * agingRender/alien->lifespan, 255-alien->age);
    }

    SDL_Rect rectangle = {alien->x, alien->y, alien->width, alien->height};
    SDL_RenderFillRect(renderer, &rectangle);
}

void mettreAJourAffichageMenu(int xBouton, int yBouton) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Button "Continue"
    SDL_Rect rectContinue = {xBouton, yBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectContinue);
    dessinerTexte("Continue", xBouton + 20, yBouton + 10, 15);

    // Button "Quit"
    SDL_Rect rectQuit = {xBouton, yBouton + hauteurBouton + espacementBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectQuit);
    dessinerTexte("Quit", xBouton + 20, yBouton + hauteurBouton + espacementBouton + 10, 15);

    // Button "Sauvegarder"
    SDL_Rect rectSauvegarder = {xBouton, yBouton + 2 * (hauteurBouton + espacementBouton), largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectSauvegarder);
    dessinerTexte("Sauvegarder", xBouton + 20, yBouton + 2 * (hauteurBouton + espacementBouton) + 10, 15);

    SDL_RenderPresent(renderer);
}

void mettreAJourAffichageSauvegarde(int xBouton, int yBouton){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Bouton "Continue"
    SDL_Rect rectSave1 = {xBouton, yBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectSave1);
    dessinerTexte("Sauvegarde 1", xBouton + 20, yBouton + 10, 15);
    SDL_Rect rectSave2 = {xBouton, yBouton + hauteurBouton + espacementBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectSave2);
    dessinerTexte("Sauvegarde 2", xBouton + 20, yBouton + hauteurBouton + espacementBouton + 10, 15);
    SDL_Rect rectSave3 = {xBouton, yBouton + 2 * (hauteurBouton + espacementBouton), largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectSave3);
    dessinerTexte("Sauvegarde 3", xBouton + 20, yBouton + 2 * (hauteurBouton + espacementBouton) + 10, 15);

    SDL_Rect rectClear1 = {xBouton + largeurBouton + espacementBouton, yBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectClear1);
    dessinerTexte("Effacer", xBouton + largeurBouton + espacementBouton + 20, yBouton + 10, 15);
    SDL_Rect rectClear2  = {xBouton + largeurBouton + espacementBouton, yBouton + hauteurBouton + espacementBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectClear2);
    dessinerTexte("Effacer", xBouton + largeurBouton + espacementBouton + 20, yBouton + hauteurBouton + espacementBouton + 10, 15);
    SDL_Rect rectClear3 = {xBouton + largeurBouton + espacementBouton, yBouton + 2 * (hauteurBouton + espacementBouton), largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectClear3);
    dessinerTexte("Effacer", xBouton + largeurBouton + espacementBouton + 20, yBouton + 2 * (hauteurBouton + espacementBouton) + 10, 15);

    SDL_Rect rectCharge1 = {xBouton + 2 * (largeurBouton + espacementBouton), yBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectCharge1);
    dessinerTexte("Charger", xBouton + 2 * (largeurBouton + espacementBouton) + 20, yBouton + 10, 15);
    SDL_Rect rectCharge2 = {xBouton + 2 * (largeurBouton + espacementBouton), yBouton + hauteurBouton + espacementBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectCharge2);
    dessinerTexte("Charger", xBouton + 2 * (largeurBouton + espacementBouton) + 20, yBouton + hauteurBouton + espacementBouton + 10, 15);
    SDL_Rect rectCharge3 = {xBouton + 2 * (largeurBouton + espacementBouton), yBouton + 2 * (hauteurBouton + espacementBouton), largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectCharge3);
    dessinerTexte("Charger", xBouton + 2 * (largeurBouton + espacementBouton) + 20, yBouton + 2 * (hauteurBouton + espacementBouton) + 10, 15);

    SDL_Rect retour = {xBouton + largeurBouton + espacementBouton, yBouton + 3 * (hauteurBouton + espacementBouton), largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &retour);
    dessinerTexte("Retour", xBouton + largeurBouton + espacementBouton + 20, yBouton + 3 * (hauteurBouton + espacementBouton) + 10, 15);

    SDL_RenderPresent(renderer);
}

void dessinerTexte(const char *texte, int x, int y, int taillePolice) {
    TTF_Font *police = TTF_OpenFont("vendor/font/Alien_Moon.ttf", taillePolice);
    if (police == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        return;
    }

    SDL_Color couleurTexte = {0, 0, 0, 255}; // Text in black
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

void actionBoutonSauvegarder(const char *nomFichier, Alien *listeAliens) {
    // Open file in wrighting mode
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
        return;
    }

    // Writing in file
    Alien *courant = listeAliens;
    while (courant != NULL) {
        fprintf(fichier, "%ld %d %d\n", courant->id, courant->x, courant->y);
        courant = courant->next;
    }

    fclose(fichier);
}

void chargerListeDepuisFichier(const char *nomFichier, Alien **listeAliens, int *numberOfAliens) {
    // Open file in reading mode
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s\n", nomFichier);
        return;
    }

    viderListeAliens(listeAliens);
    long id;
    int x, y;

    // Read file and update aliens
    while (fscanf(fichier, "%ld %d %d", &id, &x, &y) == 3) {
        ajouterAlienDepuisFichier(listeAliens, numberOfAliens, id, x, y);
    }

    fclose(fichier);
}

void viderFichier(const char *chemin) {
    FILE *fichier = fopen(chemin, "w");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier en écriture");
        return;
    }

    fprintf(fichier, "");

    fclose(fichier);
}