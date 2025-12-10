#include <stdio.h>
#include "common/ui.h"
#include "tasks/task1/compte_est_bon.h"
#include "tasks/task2/mastermind.h"
#include "tasks/task3/course_robots.h"
#include "tasks/task4/tri_ultime.h"

int main() {
    int choice;
    
    do {
        displayMainMenu();
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            displayFeedback("Entrée invalide!", 0);
            waitForEnter();
            continue;
        }
        while(getchar() != '\n');
        
        switch(choice) {
            case 1:
                playCompteEstBon();
                break;
                
            case 2:
                playMastermind();
                break;
                
            case 3:
                playCourseRobots();
                break;
                
            case 4:
                playTriUltime();
                break;
                
            case 0:
                clearScreen();
                printf("\n");
                printf("  ╔══════════════════════════════════════════════╗\n");
                printf("  ║                                              ║\n");
                printf("  ║             Merci d'avoir joué!              ║\n");
                printf("  ║                                              ║\n");
                printf("  ║              À bientôt!                      ║\n");
                printf("  ║                                              ║\n");
                printf("  ╚══════════════════════════════════════════════╝\n");
                printf("\n");
                break;
                
            default:
                displayFeedback("Choix invalide! Choisissez 0-5.", 0);
                waitForEnter();
        }
        
    } while(choice != 0);
    
    return 0;
}