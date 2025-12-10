#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "compte_est_bon.h"
#include "../../common/ui.h" 

// Définition des variables globales
Step steps[MAX_STEPS];
int stepCount = 0;
int solutionFound = 0;

// Fonction pour comparer deux doubles avec une tolérance
int equals(double a, double b) {
    return fabs(a - b) < EPS;
}

// Fonction pour trier en ordre décroissant
void sortDescending(double arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[i]) {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Fonction pour réinitialiser le solveur
void resetSolver(void) {
    stepCount = 0;
    solutionFound = 0;
}

// Fonction récursive pour résoudre le problème
int solve(double nums[], int n, double target) {
    // Cas de base : vérifier si un des nombres est égal à la cible
    for (int i = 0; i < n; i++) {
        if (equals(nums[i], target)) {
            solutionFound = 1;
            return 1;
        }
    }
    
    // Si on a qu'un seul nombre et qu'il n'est pas la cible
    if (n == 1) {
        return 0;
    }
    
    // Essayer toutes les paires de nombres
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double a = nums[i];
            double b = nums[j];
            
            // Créer un nouveau tableau sans nums[i] et nums[j]
            double newNums[MAX_NUMBERS];
            int newN = 0;
            
            for (int k = 0; k < n; k++) {
                if (k != i && k != j) {
                    newNums[newN++] = nums[k];
                }
            }
            
            // Essayer les 4 opérations
            double results[4];
            char ops[4] = {'+', '-', '*', '/'};
            
            results[0] = a + b;
            results[1] = a - b;
            results[2] = a * b;
            results[3] = (fabs(b) > EPS) ? a / b : -1;
            
            for (int op = 0; op < 4; op++) {
                // Vérifier si l'opération est valide
                if (op == 3 && fabs(b) < EPS) continue;
                if (op == 1 && results[1] < -EPS) continue;
                
                // Ajouter le résultat au nouveau tableau
                newNums[newN] = results[op];
                
                // Enregistrer l'étape
                if (stepCount < MAX_STEPS) {
                    steps[stepCount].a = a;
                    steps[stepCount].b = b;
                    steps[stepCount].r = results[op];
                    steps[stepCount].op = ops[op];
                    stepCount++;
                }
                
                // Récursion
                if (solve(newNums, newN + 1, target)) {
                    return 1;
                }
                
                // Backtrack
                stepCount--;
            }
            
            // Essayer b - a
            if (b > a + EPS) {
                double result = b - a;
                newNums[newN] = result;
                
                if (stepCount < MAX_STEPS) {
                    steps[stepCount].a = b;
                    steps[stepCount].b = a;
                    steps[stepCount].r = result;
                    steps[stepCount].op = '-';
                    stepCount++;
                }
                
                if (solve(newNums, newN + 1, target)) {
                    return 1;
                }
                
                stepCount--;
            }
        }
    }
    
    return 0;
}

// Fonction pour afficher la solution
void printSolution(void) {
    if (stepCount == 0) {
        printf(COLOR_CYAN "   >> La cible etait deja dans les nombres!\n" COLOR_RESET);
        return;
    }
    
    printf("\n");
    printf(COLOR_YELLOW "  Etapes de la Solution:\n" COLOR_RESET);
    printf(COLOR_CYAN "  ----------------------\n" COLOR_RESET);
    
    for (int i = 0; i < stepCount; i++) {
        printf(COLOR_WHITE "  %d. " COLOR_RESET, i + 1);
        
        if (steps[i].op == '+') {
            printf(COLOR_CYAN "%.0f" COLOR_RESET " + " COLOR_CYAN "%.0f" COLOR_RESET " = " COLOR_GREEN "%.0f\n" COLOR_RESET, 
                   steps[i].a, steps[i].b, steps[i].r);
        } else if (steps[i].op == '-') {
            printf(COLOR_CYAN "%.0f" COLOR_RESET " - " COLOR_CYAN "%.0f" COLOR_RESET " = " COLOR_GREEN "%.0f\n" COLOR_RESET, 
                   steps[i].a, steps[i].b, steps[i].r);
        } else if (steps[i].op == '*') {
            printf(COLOR_CYAN "%.0f" COLOR_RESET " x " COLOR_CYAN "%.0f" COLOR_RESET " = " COLOR_GREEN "%.0f\n" COLOR_RESET, 
                   steps[i].a, steps[i].b, steps[i].r);
        } else if (steps[i].op == '/') {
            printf(COLOR_CYAN "%.0f" COLOR_RESET " / " COLOR_CYAN "%.0f" COLOR_RESET " = " COLOR_GREEN "%.0f\n" COLOR_RESET, 
                   steps[i].a, steps[i].b, steps[i].r);
        }
    }
    printf("\n");
}

// Fonction pour valider une opération du joueur
int validateOperation(double available[], int *count, double a, double b, char op, double *result) {
    // Vérifier que les nombres existent
    int indexA = -1, indexB = -1;
    
    // Chercher le premier nombre
    for (int i = 0; i < *count; i++) {
        if (equals(available[i], a)) {
            indexA = i;
            break;
        }
    }
    
    // Chercher le deuxième nombre (différent du premier si même valeur)
    for (int i = 0; i < *count; i++) {
        if (i != indexA && equals(available[i], b)) {
            indexB = i;
            break;
        }
    }
    
    if (indexA == -1 || indexB == -1) {
        return 0; // Nombre non disponible
    }
    
    // Calculer le résultat
    switch(op) {
        case '+':
            *result = a + b;
            break;
        case '-':
            *result = a - b;
            if (*result < -EPS) {
                printf(COLOR_RED "  [ERREUR] Resultat negatif non autorise!\n" COLOR_RESET);
                return 0;
            }
            break;
        case '*':
        case 'x':
        case 'X':
            *result = a * b;
            break;
        case '/':
            if (fabs(b) < EPS) {
                printf(COLOR_RED "  [ERREUR] Division par zero!\n" COLOR_RESET);
                return 0;
            }
            if (fabs(fmod(a, b)) > EPS) {
                printf(COLOR_RED "  [ERREUR] Division non entiere!\n" COLOR_RESET);
                return 0;
            }
            *result = a / b;
            break;
        default:
            printf(COLOR_RED "  [ERREUR] Operation inconnue: %c\n" COLOR_RESET, op);
            return 0;
    }
    
    // Retirer a et b de la liste disponible
    double newAvailable[MAX_NUMBERS];
    int newCount = 0;
    for (int i = 0; i < *count; i++) {
        if (i != indexA && i != indexB) {
            newAvailable[newCount++] = available[i];
        }
    }
    
    // Ajouter le résultat
    newAvailable[newCount++] = *result;
    
    // Copier le nouveau tableau
    for (int i = 0; i < newCount; i++) {
        available[i] = newAvailable[i];
    }
    *count = newCount;
    
    return 1;
}

// Fonction principale du jeu
void playCompteEstBon(void) {
    displayWelcome("Le Compte est Bon");
    
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_YELLOW "     Regles du Jeu:\n" COLOR_RESET);
    printf(COLOR_CYAN "     --------------\n" COLOR_RESET);
    printf("      - Utilisez les nombres donnes\n");
    printf("      - Avec les operations: " COLOR_MAGENTA "+ - x /\n" COLOR_RESET);
    printf("      - Pour atteindre le nombre cible\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    
    srand(time(NULL));
    
    // Générer un nombre cible entre 100 et 999
    int target = 100 + rand() % 900;
    
    // Générer 6 nombres aléatoires
    double numbers[6];
    double available[MAX_NUMBERS];
    int possibleNumbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25, 50, 75, 100};
    int numPossible = 14;
    
    printf("\n");
    printf(COLOR_YELLOW "  >> Generation du probleme...\n" COLOR_RESET);
    printf("\n");
    
    for (int i = 0; i < 6; i++) {
        numbers[i] = possibleNumbers[rand() % numPossible];
        available[i] = numbers[i];
    }
    int availableCount = 6;
    
    // Vérifier qu'il existe une solution
    resetSolver();
    double tempNumbers[6];
    for (int i = 0; i < 6; i++) tempNumbers[i] = numbers[i];
    
    int hasSolution = solve(tempNumbers, 6, (double)target);
    
    if (!hasSolution) {
        // Si pas de solution, donner un problème simple
        target = 100;
        numbers[0] = 50;
        numbers[1] = 25;
        numbers[2] = 10;
        numbers[3] = 10;
        numbers[4] = 5;
        numbers[5] = 2;
        for (int i = 0; i < 6; i++) available[i] = numbers[i];
    }
    
    // Afficher le problème
    printf(COLOR_BOLD "     Nombre Cible: " COLOR_GREEN "%d\n" COLOR_RESET, target);
    printf("\n");
    printf(COLOR_WHITE "     Nombres Disponibles: " COLOR_RESET);
    for (int i = 0; i < 6; i++) {
        printf(COLOR_CYAN "%.0f" COLOR_RESET, numbers[i]);
        if (i < 5) printf(", ");
    }
    printf("\n\n");
    
    // Phase de jeu
    time_t startTime = time(NULL);
    int moves = 0;
    int maxMoves = 10;
    
    printf(COLOR_YELLOW "  >> A vous de jouer! (max %d operations)\n" COLOR_RESET, maxMoves);
    printf(COLOR_CYAN "     Format: nombre1 operation nombre2 (ex: 50 + 25)\n" COLOR_RESET);
    printf(COLOR_CYAN "     Tapez 'abandon' pour voir la solution\n" COLOR_RESET);
    printf("\n");
    
    while (moves < maxMoves) {
        // Afficher les nombres disponibles
        printf(COLOR_WHITE "  Disponibles: " COLOR_RESET);
        for (int i = 0; i < availableCount; i++) {
            printf(COLOR_CYAN "%.0f" COLOR_RESET, available[i]);
            if (i < availableCount - 1) printf(", ");
        }
        printf("\n");
        
        // Vérifier si le joueur a gagné
        for (int i = 0; i < availableCount; i++) {
            if (equals(available[i], target)) {
                time_t endTime = time(NULL);
                int timeUsed = (int)difftime(endTime, startTime);
                
                printf("\n");
                printf(COLOR_GREEN "  ====================================================\n" COLOR_RESET);
                printf(COLOR_BOLD "     BRAVO! Le compte est bon!\n" COLOR_RESET);
                printf(COLOR_GREEN "  ====================================================\n" COLOR_RESET);
                printf(COLOR_YELLOW "     Operations: %d\n" COLOR_RESET, moves);
                printf(COLOR_YELLOW "     Temps: %d secondes\n" COLOR_RESET, timeUsed);
                
                int score = 1000 - (moves * 50) - (timeUsed * 2);
                if (score < 0) score = 0;
                printf(COLOR_GREEN "     Score: %d points\n" COLOR_RESET, score);
                printf("\n");
                waitForEnter();
                return;
            }
        }
        
        // Vérifier si c'est encore possible
        if (availableCount == 1 && !equals(available[0], target)) {
            printf("\n");
            printf(COLOR_RED "  Plus d'operations possibles!\n" COLOR_RESET);
            printf(COLOR_YELLOW "  Vous avez atteint: %.0f (cible: %d)\n" COLOR_RESET, available[0], target);
            printf(COLOR_YELLOW "  >> Voulez-vous voir la solution? (o/n): " COLOR_RESET);
            
            char response[10];
            if (fgets(response, sizeof(response), stdin) != NULL) {
                if (response[0] == 'o' || response[0] == 'O') {
                    printf("\n");
                    printf(COLOR_YELLOW "  >> Voici la solution:\n" COLOR_RESET);
                    resetSolver();
                    solve(numbers, 6, (double)target);
                    printSolution();
                }
            }
            waitForEnter();
            return;
        }
        
        // Lire l'entrée du joueur
        printf(COLOR_YELLOW "  >> Operation %d: " COLOR_RESET, moves + 1);
        char input[100];
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        // Retirer le \n
        input[strcspn(input, "\n")] = 0;
        
        // Vérifier abandon
        if (strcmp(input, "abandon") == 0) {
            printf("\n");
            printf(COLOR_YELLOW "  >> Voici la solution:\n" COLOR_RESET);
            resetSolver();
            solve(numbers, 6, (double)target);
            printSolution();
            waitForEnter();
            return;
        }
        
        // Parser l'entrée
        double a, b, result;
        char op;
        
        // Essayer différents formats
        int parsed = 0;
        
        // Format avec espaces: "50 + 50"
        if (sscanf(input, "%lf %c %lf", &a, &op, &b) == 3) {
            parsed = 1;
        }
        // Format sans espaces: "50+50"
        else if (sscanf(input, "%lf%c%lf", &a, &op, &b) == 3) {
            parsed = 1;
        }
        
        if (!parsed) {
            displayFeedback("Format invalide! Utilisez: nombre1 operation nombre2", 0);
            continue;
        }
        
        // Valider l'opération
        if (validateOperation(available, &availableCount, a, b, op, &result)) {
            moves++;
            printf(COLOR_GREEN "  [OK] %.0f %c %.0f = %.0f\n" COLOR_RESET, a, op, b, result);
        } else {
            displayFeedback("Operation invalide!", 0);
        }
        
        printf("\n");
    }
    
    // Si le joueur n'a pas trouvé
    printf(COLOR_RED "  Dommage! Limite d'operations atteinte.\n" COLOR_RESET);
    printf(COLOR_YELLOW "  >> Voici la solution:\n" COLOR_RESET);
    resetSolver();
    solve(numbers, 6, (double)target);
    printSolution();
    
    waitForEnter();
}