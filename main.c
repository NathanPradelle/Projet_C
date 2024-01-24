
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

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

int main(/*int argc, char *argv[]*/) {
    int screenWidth, screenHeight;
    windowsConfig(&screenWidth, &screenHeight);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    SDL_Window *fenetre = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (fenetre == NULL) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    // Boucle d'événements SDL
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}
