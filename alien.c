#include "alien.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

float defaultSpeed = 0.5;
int alienTravelDistance = 1;
int alienWidth, alienHeight = 10;
float alienLifespan = 5000;

int alienConfig(float *defaultSpeed, int *alienTravelDistance, int *alienWidth, int *alienHeight, float *alienLifespan) {
    FILE *configFile = fopen("config.txt", "r");
    if (configFile == NULL) {
        perror("Impossible d'ouvrir le fichier de configuration");
        return 1;
    }

    char line[150];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        sscanf(line, "DEFAULT_SPEED=%f", defaultSpeed);
        sscanf(line, "DEFAULT_TRAVEL_DISTANCE=%d", alienTravelDistance);
        sscanf(line, "ALIEN_WIDTH=%d", alienWidth);
        sscanf(line, "ALIEN_HEIGHT=%d", alienHeight);
        sscanf(line, "ALIEN_LIFESPAN=%f", alienLifespan);
    }

    fclose(configFile);
    return 0;
}

Alien *creerAlien(int *numberOfAliens) {   
    alienConfig(&defaultSpeed, &alienTravelDistance, &alienWidth, &alienHeight, &alienLifespan);

    ++*numberOfAliens;
    Alien *nouvelAlien = (Alien *)malloc(sizeof(Alien));
    if (nouvelAlien != NULL) {
        nouvelAlien->alive=1;
        nouvelAlien->id = *numberOfAliens;
        nouvelAlien->x = rand() % (screenWidth - alienWidth);
        nouvelAlien->y = rand() % (screenHeight - alienHeight);
        nouvelAlien->speed = defaultSpeed;
        nouvelAlien->travelDistance = alienTravelDistance;
        nouvelAlien->width = alienWidth;
        nouvelAlien->height = alienHeight;
        nouvelAlien->time = 0;
        nouvelAlien->age = 0;
        nouvelAlien->lifespan = alienLifespan;
        nouvelAlien->type = rand() % 3;
        nouvelAlien->next = NULL;
    }
    return nouvelAlien;
}

void ajouterAlien(Alien **liste, int *numberOfAliens) {
    Alien *nouvelAlien = creerAlien(numberOfAliens);
    if (nouvelAlien != NULL) {
        if (*liste == NULL) {
            *liste = nouvelAlien;
        } else {
            Alien *courant = *liste;
            while (courant->next != NULL) {
                courant = courant->next;
            }
            courant->next = nouvelAlien;
        }
    }
}

void detruireAlien(Alien *alien) {
    free(alien);
}

void deplacerAlien(Alien *alien) {
    int direction = rand() % 5;

    alien->age++;
    alien->time++;

    if (alien->time * alien->speed > 500) {
        switch (direction) {
            case 0:
                if (alien->y > alien->height + alien->travelDistance) {
                    alien->y -= alien->travelDistance;
                }
                break;
            case 1:
                if (alien->y < screenHeight - alien->height - alien->travelDistance) {  
                    alien->y += alien->travelDistance;
                }
                break;
            case 2:
                if (alien->x > alien->width + alien->travelDistance) {
                    alien->x -= alien->travelDistance;
                }
                break;
            case 3:
                if (alien->x < screenWidth - alien->width - alien->travelDistance) {  
                    alien->x += alien->travelDistance;
                }
                break;
        }
        alien->time = 0;
    }
}

void ajouterAlienDepuisFichier(Alien **liste, int *numberOfAliens, long id, int x, int y) {
    Alien *nouvelAlien = creerAlien(numberOfAliens);
    if (nouvelAlien != NULL) {
        nouvelAlien->id = id;
        nouvelAlien->x = x;
        nouvelAlien->y = y;

        if (*liste == NULL) {
            *liste = nouvelAlien;
        } else {
            Alien *courant = *liste;
            while (courant->next != NULL) {
                courant = courant->next;
            }
            courant->next = nouvelAlien;
        }
    }
}

void viderListeAliens(Alien **listeAliens) {
    while (*listeAliens != NULL) {
        Alien *suivant = (*listeAliens)->next;
        free(*listeAliens);  // Libérer la mémoire de l'élément actuel
        *listeAliens = suivant;
    }
}