#include "graphics.h"

SDL_Renderer *renderer = NULL;
SDL_Window *fenetre = NULL;
int screenWidth, screenHeight;
int largeurBouton = 200;
int hauteurBouton = 50;
int espacementBouton = 20;
int xBouton;
int yBouton;



int windowsConfig(int * screenWidth, int * screenHeight) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    char line[150];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        sscanf(line, "SCREEN_WIDTH=%d", screenWidth);
        sscanf(line, "SCREEN_HEIGHT=%d", screenHeight);
    }

    fclose(configFile);
    return 0;
}

void initSDL() {
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
    TTF_Init();
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
            if (alien1->x < alien2->x + alien2->width &&
                alien1->x + alien1->width > alien2->x &&
                alien1->y < alien2->y + alien2->height &&
                alien1->y + alien1->height > alien2->y) {
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

void itemGenerer(SDL_Renderer* renderer, int x, int y, int size, SDL_Color fillColor, SDL_Color borderColor) {
    // Dessiner le carré rempli avec la couleur de fond
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_Rect squareRect = {x, y, size, size};
    SDL_RenderFillRect(renderer, &squareRect);

    // Dessiner les contours du carré avec la couleur de la bordure
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &squareRect);
}

void dessinerAlien(const Alien *alien) {
    if(alien->alive==0 || alien->age>=200){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    } else {
        if(alien->type==0){
            SDL_SetRenderDrawColor(renderer, 255, 255-alien->age, 255-alien->age, 255-alien->age);
        }
        if(alien->type==1){
            SDL_SetRenderDrawColor(renderer, 255-alien->age, 255, 255-alien->age, 255-alien->age);
        }
        if(alien->type==2){
            SDL_SetRenderDrawColor(renderer, 255-alien->age, 255-alien->age, 255, 255-alien->age);
        }
    }
    SDL_Rect rectangle = {alien->x, alien->y, alien->width, alien->height};
    SDL_RenderFillRect(renderer, &rectangle);
}

void mettreAJourAffichageMenu(int xBouton, int yBouton) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Bouton "Continue"
    SDL_Rect rectContinue = {xBouton, yBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectContinue);
    dessinerTexte("Continue", xBouton + 20, yBouton + 10, 15);

    // Bouton "Quit"
    SDL_Rect rectQuit = {xBouton, yBouton + hauteurBouton + espacementBouton, largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectQuit);
    dessinerTexte("Quit", xBouton + 20, yBouton + hauteurBouton + espacementBouton + 10, 15);

    // Bouton "Sauvegarder"
    SDL_Rect rectSauvegarder = {xBouton, yBouton + 2 * (hauteurBouton + espacementBouton), largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectSauvegarder);
    dessinerTexte("Sauvegarder", xBouton + 20, yBouton + 2 * (hauteurBouton + espacementBouton) + 10, 15);

    SDL_Rect rectCharge = {xBouton, yBouton + 3 * (hauteurBouton + espacementBouton), largeurBouton, hauteurBouton};
    SDL_RenderFillRect(renderer, &rectCharge);
    dessinerTexte("Charger", xBouton + 20, yBouton + 3 * (hauteurBouton + espacementBouton) + 10, 15);

    SDL_RenderPresent(renderer);
}


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

void actionBoutonSauvegarder(const char *nomFichier, Alien *listeAliens) {
    // Ouverture du fichier en mode écriture
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
        return;
    }

    // Parcours de la liste et écriture dans le fichier
    Alien *courant = listeAliens;
    while (courant != NULL) {
        fprintf(fichier, "%ld %d %d\n", courant->id, courant->x, courant->y);
        courant = courant->next;
    }

    // Fermeture du fichier
    fclose(fichier);
}

void chargerListeDepuisFichier(const char *nomFichier, Alien **listeAliens, int *numberOfAliens) {
    // Ouvrir le fichier en mode lecture
    long id;
    int x, y;
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier : %s\n", nomFichier);
        return;
    }

    // Lire les données du fichier et mettre à jour la liste
    while (fscanf(fichier, "%ld %d %d", &id, &x, &y) == 3) {
        ajouterAlienDepuisFichier(listeAliens, numberOfAliens, id, x, y);
    }

    // Fermer le fichier
    fclose(fichier);
}