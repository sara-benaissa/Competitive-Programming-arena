#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Function Declarations

void clearScreen(void);

void displayMainMenu(void);

void displayWelcome(const char* taskName);

void displayGameStatus(int attempts, int maxAttempts, int timeElapsed);

void displayScore(int score, int attempts, int timeSeconds);

void displayFeedback(const char* message, int isSuccess);

void waitForEnter(void);

#endif 
