#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

// ANSI Color Codes
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_WHITE   "\033[1;37m"
#define COLOR_BOLD    "\033[1m"

// Background colors
#define BG_RED        "\033[41m"
#define BG_GREEN      "\033[42m"
#define BG_BLUE       "\033[44m"

// Clear the screen (cross-platform)
void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Display Main Menu
void displayMainMenu(void) {
    clearScreen();
    printf("\n\n");
    printf(COLOR_CYAN "  ****************************************************\n");
    printf("  *                                                  *\n");
    printf("  *" COLOR_YELLOW "      ARENA DE DEFIS ALGORITHMIQUES              " COLOR_CYAN "*\n");
    printf("  *" COLOR_WHITE "      Ecole Nationale des Sciences                " COLOR_CYAN "*\n");
    printf("  *" COLOR_WHITE "           de l'Informatique                      " COLOR_CYAN "*\n");
    printf("  *                                                  *\n");
    printf("  ****************************************************\n" COLOR_RESET);
    printf("\n\n");
    printf(COLOR_BOLD "          Choose a challenge:\n" COLOR_RESET);
    printf(COLOR_CYAN "          -------------------\n\n" COLOR_RESET);
    printf(COLOR_GREEN "          1" COLOR_RESET " > Le Compte est Bon\n");
    printf(COLOR_GREEN "          2" COLOR_RESET " > Mastermind Algorithmique\n");
    printf(COLOR_GREEN "          3" COLOR_RESET " > Course de Robots\n");
    printf(COLOR_GREEN "          4" COLOR_RESET " > Tri Ultime\n");
    printf(COLOR_RED "          0" COLOR_RESET " > Quit\n");
    printf("\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_YELLOW "  >> Your choice: " COLOR_RESET);
}

// Display Welcome Screen for a Task
void displayWelcome(const char* taskName) {
    clearScreen();
    printf("\n\n");
    printf(COLOR_CYAN "  ****************************************************\n");
    printf("  *                                                  *\n" COLOR_RESET);
    
    int nameLen = strlen(taskName);
    int totalWidth = 50;
    int padding = (totalWidth - nameLen) / 2;
    
    printf(COLOR_CYAN "  *" COLOR_RESET);
    for (int i = 0; i < padding; i++) printf(" ");
    printf(COLOR_YELLOW "%s" COLOR_RESET, taskName);
    for (int i = 0; i < (totalWidth - nameLen - padding); i++) printf(" ");
    printf(COLOR_CYAN "*\n");
    
    printf("  *                                                  *\n");
    printf("  ****************************************************\n" COLOR_RESET);
    printf("\n\n");
}

// Display Game Status (attempts, time)
void displayGameStatus(int attempts, int maxAttempts, int timeElapsed) {
    printf("\n");
    printf(COLOR_BLUE "  +--------------------------------------------------+\n");
    printf("  | " COLOR_RESET "Attempt: " COLOR_CYAN "%2d" COLOR_RESET "/" COLOR_CYAN "%2d" COLOR_RESET "        Time: " COLOR_YELLOW "%3d" COLOR_RESET " seconds" COLOR_BLUE "      |\n" COLOR_RESET, 
           attempts, maxAttempts, timeElapsed);
    printf(COLOR_BLUE "  +--------------------------------------------------+\n" COLOR_RESET);
    printf("\n");
}

// Display Final Score

void displayScore(int score, int attempts, int timeSeconds) {
    printf("\n\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_BOLD "                 FINAL RESULTS                        \n" COLOR_RESET);
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_YELLOW "      Game Statistics:\n" COLOR_RESET);
    printf(COLOR_CYAN "      --------------------------\n" COLOR_RESET);
    printf("        > Attempts used  : " COLOR_MAGENTA "%d\n" COLOR_RESET, attempts);
    printf("        > Time elapsed   : " COLOR_YELLOW "%d" COLOR_RESET " seconds\n", timeSeconds);
    printf("        > Final score    : " COLOR_GREEN "%d" COLOR_RESET " points\n", score);
    printf("\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");
}

// Display Feedback Message
void displayFeedback(const char* message, int isSuccess) {
    printf("\n");
    if (isSuccess) {
        printf(COLOR_GREEN "  [✓ SUCCESS] " COLOR_RESET "%s\n", message);
    } else {
        printf(COLOR_RED "  [✗ ERROR] " COLOR_RESET "%s\n", message);
    }
    printf("\n");
}

// Wait for User to Press Enter
void waitForEnter(void) {
    printf(COLOR_CYAN "  >> Press Enter to continue..." COLOR_RESET);
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    getchar();
}