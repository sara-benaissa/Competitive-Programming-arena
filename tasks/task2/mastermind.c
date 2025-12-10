#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mastermind.h"
#include "../../common/ui.h"

// ANSI Color Codes (matching ui.c)
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_WHITE   "\033[1;37m"
#define COLOR_BOLD    "\033[1m"

// Function 1: Generate Random Secret Code
void generateSecret(int secret[], int length) {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    
    for (int i = 0; i < length; i++) {
        secret[i] = rand() % 10;
    }
}

// Function 2: Calculate Final Score
int calculateScore(int attempts, int timeSeconds) {
    int baseScore = 1000;
    int attemptPenalty = attempts * 50;
    int timePenalty = timeSeconds * 2;
    
    int finalScore = baseScore - attemptPenalty - timePenalty;
    
    if (finalScore < 0) {
        return 0;
    }
    
    return finalScore;
}

// Function 3: Display Mastermind Feedback
void displayMastermindFeedback(int correct, int misplaced) {
    printf("\n");
    printf(COLOR_CYAN "  +--------------------------------------+\n");
    printf("  | " COLOR_RESET COLOR_BOLD "RESULTAT:" COLOR_CYAN "                           |\n");
    printf("  +--------------------------------------+\n");
    printf("  | " COLOR_RESET COLOR_GREEN "[OK] Bien places: " COLOR_WHITE "%d" COLOR_CYAN "             |\n", correct);
    printf("  | " COLOR_RESET COLOR_YELLOW "[  ] Mal places:  " COLOR_WHITE "%d" COLOR_CYAN "             |\n", misplaced);
    printf("  +--------------------------------------+\n" COLOR_RESET);
}

// Function 4: Get User's Guess
void getUserGuess(int guess[], int length) {
    printf("\n" COLOR_YELLOW "  >> Entrez %d chiffres (0-9) separes par des espaces: " COLOR_RESET, length);
    
    for (int i = 0; i < length; i++) {
        int input;
        
        if (scanf("%d", &input) != 1) {
            displayFeedback("Entree invalide! Utilisez des chiffres 0-9.", 0);
            
            while (getchar() != '\n');
            
            i--;
            continue;
        }
        
        if (input < MIN_DIGIT || input > MAX_DIGIT) {
            displayFeedback("Chiffre hors limite! Utilisez 0-9.", 0);
            i--;  
            continue;
        }
        
        guess[i] = input;
    }
    
    while (getchar() != '\n');
}

// Function 5: Check Guess Against Secret
void checkGuess(int secret[], int guess[], int length, 
                int *correct, int *misplaced) {
    
    *correct = 0;
    *misplaced = 0;
    
    int secretUsed[CODE_LENGTH] = {0};  
    int guessUsed[CODE_LENGTH] = {0};
    
    for (int i = 0; i < length; i++) {
        if (guess[i] == secret[i]) {
            (*correct)++;           
            secretUsed[i] = 1;      
            guessUsed[i] = 1;       
        }
    }
    
    for (int i = 0; i < length; i++) {
        if (guessUsed[i]) {
            continue;
        }
        
        for (int j = 0; j < length; j++) {
            if (secretUsed[j]) {
                continue;
            }
            
            if (guess[i] == secret[j]) {
                (*misplaced)++;      
                secretUsed[j] = 1;   
                break;             
            }
        }
    }
}

// Function 6: Main Game Loop
void playMastermind() {
    Game game;
    int currentGuess[CODE_LENGTH];
    int correct, misplaced;
    int won = 0;
    
    game.attempts = 0;
    game.score = 0;
    
    displayWelcome("MASTERMIND ALGORITHMIQUE");
    
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_BOLD "                 REGLES DU JEU                        \n" COLOR_RESET);
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_WHITE "    o Devinez une sequence de %d chiffres (0-9)\n", CODE_LENGTH);
    printf("    o Vous avez %d tentatives maximum\n", MAX_ATTEMPTS);
    printf("    o Moins d'essais = Meilleur score!\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_BOLD "                    FEEDBACK                          \n" COLOR_RESET);
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_GREEN "    [OK] Bien places: " COLOR_WHITE "Bon chiffre, bonne position\n" COLOR_RESET);
    printf(COLOR_YELLOW "    [  ] Mal places:  " COLOR_WHITE "Bon chiffre, mauvaise position\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");
    
    waitForEnter();
    
    generateSecret(game.secret, CODE_LENGTH);
    
    /*
    printf(COLOR_MAGENTA "  [DEBUG] Secret: " COLOR_RESET);
    for (int i = 0; i < CODE_LENGTH; i++) {
        printf(COLOR_BOLD "%d " COLOR_RESET, game.secret[i]);
    }
    printf("\n\n");*/
    
    time_t startTime = time(NULL);
    
    while (game.attempts < MAX_ATTEMPTS && !won) {
        game.attempts++;
        game.timeSeconds = (int)difftime(time(NULL), startTime);
        
        displayGameStatus(game.attempts, MAX_ATTEMPTS, game.timeSeconds);
        
        getUserGuess(currentGuess, CODE_LENGTH);
        
        checkGuess(game.secret, currentGuess, CODE_LENGTH, 
                   &correct, &misplaced);
        
        displayMastermindFeedback(correct, misplaced);
        
        if (correct == CODE_LENGTH) {
            won = 1;
        }
    }
    
    game.timeSeconds = (int)difftime(time(NULL), startTime);
    
    clearScreen();
    printf("\n\n");
    
    if (won) {
        printf(COLOR_GREEN "  ====================================================\n");
        printf("                                                      \n");
        printf(COLOR_RESET COLOR_BOLD "            FELICITATIONS!                             \n" COLOR_RESET);
        printf(COLOR_WHITE "        Vous avez trouve la solution!                  \n" COLOR_RESET);
        printf(COLOR_GREEN "                                                      \n");
        printf("  ====================================================\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "  ====================================================\n");
        printf("                                                      \n");
        printf(COLOR_RESET COLOR_BOLD "               DOMMAGE!                                \n" COLOR_RESET);
        printf(COLOR_WHITE "        Vous avez epuise vos tentatives.              \n" COLOR_RESET);
        printf(COLOR_RED "                                                      \n");
        printf("  ====================================================\n" COLOR_RESET);
    }
    
    printf("\n");
    printf(COLOR_CYAN "  +--------------------------------------+\n");
    printf("  | " COLOR_RESET COLOR_BOLD "La solution etait:" COLOR_CYAN "              |\n");
    printf("  | " COLOR_RESET);
    for (int i = 0; i < CODE_LENGTH; i++) {
        printf(COLOR_YELLOW "%d " COLOR_RESET, game.secret[i]);
    }
    printf(COLOR_CYAN "                        |\n");
    printf("  +--------------------------------------+\n" COLOR_RESET);
    printf("\n");
    
    game.score = calculateScore(game.attempts, game.timeSeconds);
    displayScore(game.score, game.attempts, game.timeSeconds);
    
    waitForEnter();
}