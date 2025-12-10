#ifndef COMPTE_EST_BON_H
#define COMPTE_EST_BON_H
#include <stdlib.h>
#include <math.h>
#define EPS 1e-6
#define MAX_STEPS 50
#define MAX_NUMBERS 10

// Structure pour stocker les étapes dans le bon ordre
typedef struct {
    double a;
    double b;
    double r;
    char op;
} Step;

// Variables globales
extern Step steps[MAX_STEPS];
extern int stepCount;
extern int solutionFound;

// Déclarations des fonctions
int equals(double a, double b);
void sortDescending(double arr[], int n);
int solve(double nums[], int n, double target);
void printSolution(void);
void resetSolver(void);

// Fonction principale du jeu
void playCompteEstBon(void);

#endif // COMPTE_EST_BON_H