

#include <stdlib.h>
#include "vendor/include/SDL.h"
#include "vendor/include/SDL_image.h"
#include "vendor/include/SDL_ttf.h"
#include "vendor/include/SDL_mixer.h"

#define hauteur 1200
#define largeur 800

#define MENU_SIZE 3

int main(int argc, char *argv[]) {

            if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
                return 1;
            }
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                printf("Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
            }
            Mix_Music *music = Mix_LoadMUS("music/Program in C.mp3");
            if (!music) {
                printf("Erreur lors du chargement du fichier MP3: %s\n", Mix_GetError());
                return 1;
            }
            if (Mix_PlayMusic(music, 1) < 0) {
                printf("Erreur lors de la lecture de la musique: %s\n", Mix_GetError());
                return 1;
            }

    SDL_Window *fenetre = SDL_CreateWindow("Ma fenêtre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, hauteur, largeur, SDL_WINDOW_SHOWN);
    if (fenetre == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Delay(2000);
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_Delay(2000);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("font/OpenSans-Bold.ttf", 20);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        SDL_Delay(2000);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return 1;
    }

    SDL_Color textColor = {255, 255, 255};

    char *menuOptions[MENU_SIZE] = {"commencer", "modifier", "quitter"};
    int selectedOption = 0;

    SDL_Texture *optionTextures[MENU_SIZE];

    SDL_Event event;
    int running = 1;

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
                            Mix_FreeMusic(music);
                            music = Mix_LoadMUS("music/Program in C.mp3");
                            if (!music) {
                                printf("Erreur lors du chargement du fichier MP3: %s\n", Mix_GetError());
                                return 1;
                            }
                            if (Mix_PlayMusic(music, 1) < 0) {
                                printf("Erreur lors de la lecture de la musique: %s\n", Mix_GetError());
                                return 1;
                            }
                        }
                        if (selectedOption == 1) {
                            
                        }
                        if (selectedOption == 2) {
                            running = 0;
                        }
                        break;
                }
            }
        }

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
                return 1;
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
                return 1;
            }

            SDL_Rect optionRect = {largeur / 2, 100 + i * (optionSurface->h + 10), optionSurface->w, optionSurface->h};

            SDL_RenderCopy(renderer, optionTextures[i], NULL, &optionRect);

            SDL_DestroyTexture(optionTextures[i]);
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}
