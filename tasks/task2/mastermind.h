#ifndef MASTERMIND_H
#define MASTERMIND_H

// Constants
#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10
#define MIN_DIGIT 0
#define MAX_DIGIT 9

// Game data structure
typedef struct {
    int secret[CODE_LENGTH];    
    int attempts;              
    int timeSeconds;            
    int score;                  
} Game;

// Mastermind function declarations
void generateSecret(int secret[], int length);
void getUserGuess(int guess[], int length);
void checkGuess(int secret[], int guess[], int length, 
                int *correct, int *misplaced);
int calculateScore(int attempts, int timeSeconds);
void displayMastermindFeedback(int correct, int misplaced);
void playMastermind();

// UI function declarations 
void displayWelcome(const char* taskName);
void displayGameStatus(int attempts, int maxAttempts, int timeElapsed);
void displayScore(int score, int attempts, int timeSeconds);
void displayFeedback(const char* message, int isSuccess);
void clearScreen(void);
void waitForEnter(void);

#endif