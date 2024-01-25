#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

// Déclaration de l'énumération ProgramState
typedef enum {
    MENU,
    SIMULATION,
    QUIT
} ProgramState;

ProgramState runSimulation();
ProgramState runMenu();

#endif // PROGRAM_STATE_H