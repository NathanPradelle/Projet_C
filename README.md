## Commande avec les bonnes options pour pouvoir compiler le projet :  
gcc -o mon_programme main.c -std=c11 -Wall -Wextra -I./vendor/include -L./vendor/lib -lSDL2 -Wl,-subsystem,windows -DSDL_MAIN_HANDLED
gcc main.c -o bin/a.exe -std=c11 -Wall -Wextra -I include -L lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -DSDL_MAIN_HANDLED

## Commande simplifier
make (oui, t'écris juste ça dans MSYS2 est ça va tout compiler)

## Commande pour lancer le programme
./alien_simulation.exe

## Ajouter un fichier à la compilation
Dans le fichier Makefile, rajoute le nom du fichier dans la ligne avec SRCS
Attention, ne pas modifier la tabulation du fichier
