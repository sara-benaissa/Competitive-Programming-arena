#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "course_robots.h"
#include "../../common/ui.h"

// ==================== FONCTIONS QUEUE ====================

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

void enqueue(Queue* q, Position pos) {
    q->positions[q->rear] = pos;
    q->rear++;
}

Position dequeue(Queue* q) {
    Position pos = q->positions[q->front];
    q->front++;
    return pos;
}

int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

// ==================== GÉNÉRATION DE LABYRINTHE ====================

void initEmptyMaze(Maze* maze) {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (rand() % 100 < 30) {
                maze->grid[i][j] = WALL;
            } else {
                maze->grid[i][j] = EMPTY;
            }
        }
    }
}

void generateRandomMaze(Maze* maze) {
    int pathExists = 0;
    int attempts = 0;

    while (!pathExists && attempts < 100) {
        initEmptyMaze(maze);

        maze->start.x = rand() % MAZE_SIZE;
        maze->start.y = rand() % (MAZE_SIZE / 2);
        maze->grid[maze->start.x][maze->start.y] = START;

        maze->end.x = rand() % MAZE_SIZE;
        maze->end.y = (MAZE_SIZE / 2) + rand() % (MAZE_SIZE / 2);
        maze->grid[maze->end.x][maze->end.y] = END;

        char testSolution[MAX_PATH_LENGTH];
        pathExists = findPath(maze, testSolution);
        attempts++;
    }

    if (!pathExists) {
        for (int i = 0; i < MAZE_SIZE; i++) {
            for (int j = 0; j < MAZE_SIZE; j++) {
                maze->grid[i][j] = EMPTY;
            }
        }

        for (int i = 0; i < 10; i++) {
            int rx = rand() % MAZE_SIZE;
            int ry = rand() % MAZE_SIZE;
            maze->grid[rx][ry] = WALL;
        }

        maze->start.x = 0;
        maze->start.y = 0;
        maze->grid[0][0] = START;

        maze->end.x = MAZE_SIZE - 1;
        maze->end.y = MAZE_SIZE - 1;
        maze->grid[MAZE_SIZE - 1][MAZE_SIZE - 1] = END;
    }
}

// ==================== AFFICHAGE ====================

void displayMaze(Maze* maze) {
    printf("\n");
    printf(COLOR_CYAN "     Labyrinthe:\n" COLOR_RESET);
    printf(COLOR_CYAN "     -----------\n" COLOR_RESET);
    printf("\n");
    
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("     ");
        for (int j = 0; j < MAZE_SIZE; j++) {
            char c = maze->grid[i][j];
            if (c == START) {
                printf(COLOR_GREEN "%c " COLOR_RESET, c);
            } else if (c == END) {
                printf(COLOR_YELLOW "%c " COLOR_RESET, c);
            } else if (c == WALL) {
                printf(COLOR_RED "%c " COLOR_RESET, c);
            } else {
                printf(COLOR_WHITE "%c " COLOR_RESET, c);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void displayMazeWithPath(Maze* maze, const char* path, int isCorrect) {
    char display[MAZE_SIZE][MAZE_SIZE];

    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            display[i][j] = maze->grid[i][j];
        }
    }

    Position current = maze->start;
    char marker = isCorrect ? PATH : WRONG;

    for (int i = 0; path[i] != '\0'; i++) {
        switch(path[i]) {
            case 'N': current.x--; break;
            case 'S': current.x++; break;
            case 'E': current.y++; break;
            case 'O': current.y--; break;
        }

        if (current.x >= 0 && current.x < MAZE_SIZE && 
            current.y >= 0 && current.y < MAZE_SIZE) {
            if (display[current.x][current.y] == EMPTY) {
                display[current.x][current.y] = marker;
            }
        }
    }

    printf("\n");
    printf(COLOR_CYAN "     Chemin visualise:\n" COLOR_RESET);
    printf(COLOR_CYAN "     -----------------\n" COLOR_RESET);
    printf("\n");

    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("     ");
        for (int j = 0; j < MAZE_SIZE; j++) {
            char c = display[i][j];
            if (c == START) {
                printf(COLOR_GREEN "%c " COLOR_RESET, c);
            } else if (c == END) {
                printf(COLOR_YELLOW "%c " COLOR_RESET, c);
            } else if (c == WALL) {
                printf(COLOR_RED "%c " COLOR_RESET, c);
            } else if (c == PATH) {
                printf(COLOR_GREEN "%c " COLOR_RESET, c);
            } else if (c == WRONG) {
                printf(COLOR_RED "%c " COLOR_RESET, c);
            } else {
                printf(COLOR_WHITE "%c " COLOR_RESET, c);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// ==================== VALIDATION ====================

int isValid(Maze* maze, Position pos, int visited[MAZE_SIZE][MAZE_SIZE]) {
    if (pos.x < 0 || pos.x >= MAZE_SIZE || 
        pos.y < 0 || pos.y >= MAZE_SIZE) {
        return 0;
    }

    if (maze->grid[pos.x][pos.y] == WALL) {
        return 0;
    }

    if (visited[pos.x][pos.y]) {
        return 0;
    }

    return 1;
}

int validateUserPath(Maze* maze, const char* userPath) {
    Position current = maze->start;

    for (int i = 0; userPath[i] != '\0'; i++) {
        char move = toupper(userPath[i]);

        if (move == ' ') continue;

        if (move != 'N' && move != 'S' && move != 'E' && move != 'O') {
            return 0;
        }

        Position next = current;
        switch(move) {
            case 'N': next.x--; break;
            case 'S': next.x++; break;
            case 'E': next.y++; break;
            case 'O': next.y--; break;
        }

        if (next.x < 0 || next.x >= MAZE_SIZE || 
            next.y < 0 || next.y >= MAZE_SIZE) {
            return 0;
        }

        if (maze->grid[next.x][next.y] == WALL) {
            return 0;
        }

        current = next;
    }

    return (current.x == maze->end.x && current.y == maze->end.y);
}

// ==================== ALGORITHME BFS ====================

void reconstructPath(Maze* maze, Position parent[MAZE_SIZE][MAZE_SIZE], char* solution) {
    char temp[MAX_PATH_LENGTH];
    int index = 0;

    Position current = maze->end;
    Position start = maze->start;

    while (!(current.x == start.x && current.y == start.y)) {
        Position prev = parent[current.x][current.y];

        if (prev.x < current.x) {
            temp[index++] = 'S';
        } else if (prev.x > current.x) {
            temp[index++] = 'N';
        } else if (prev.y < current.y) {
            temp[index++] = 'E';
        } else {
            temp[index++] = 'O';
        }

        current = prev;
    }

    for (int i = 0; i < index; i++) {
        solution[i] = temp[index - 1 - i];
    }
    solution[index] = '\0';
}

int findPath(Maze* maze, char* solution) {
    Queue q;
    initQueue(&q);

    int visited[MAZE_SIZE][MAZE_SIZE] = {0};
    Position parent[MAZE_SIZE][MAZE_SIZE];

    enqueue(&q, maze->start);
    visited[maze->start.x][maze->start.y] = 1;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    int found = 0;

    while (!isQueueEmpty(&q)) {
        Position current = dequeue(&q);

        if (current.x == maze->end.x && current.y == maze->end.y) {
            found = 1;
            break;
        }

        for (int i = 0; i < 4; i++) {
            Position next;
            next.x = current.x + dx[i];
            next.y = current.y + dy[i];

            if (isValid(maze, next, visited)) {
                visited[next.x][next.y] = 1;
                parent[next.x][next.y] = current;
                enqueue(&q, next);
            }
        }
    }

    if (found) {
        reconstructPath(maze, parent, solution);
    }

    return found;
}

// ==================== SYSTÈME DE SCORE ====================

int calculateScore1(int pathLength, int timeUsed, int isOptimal) {
    int score = 1000;

    if (isOptimal) {
        score += 500;
    }

    score -= timeUsed * 5;

    if (!isOptimal) {
        score -= pathLength * 10;
    }

    if (score < 0) score = 0;

    return score;
}

// ==================== FONCTION PRINCIPALE DU JEU ====================

void playCourseRobots() {
    Maze maze;
    char optimalSolution[MAX_PATH_LENGTH];
    char userPath[MAX_PATH_LENGTH];

    srand(time(NULL));

    displayWelcome("Course de Robots");

    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_YELLOW "     Regles du Jeu:\n" COLOR_RESET);
    printf(COLOR_CYAN "     --------------\n" COLOR_RESET);
    printf("      - Trouvez le chemin de " COLOR_GREEN "S" COLOR_RESET " (depart) vers " COLOR_YELLOW "E" COLOR_RESET " (arrivee)\n");
    printf("      - Commandes: " COLOR_MAGENTA "N" COLOR_RESET " (Nord), " COLOR_MAGENTA "S" COLOR_RESET " (Sud), " COLOR_MAGENTA "E" COLOR_RESET " (Est), " COLOR_MAGENTA "O" COLOR_RESET " (Ouest)\n");
    printf("      - Exemple: " COLOR_CYAN "SSEEENNO\n" COLOR_RESET);
    printf("      - Temps limite: " COLOR_RED "60 secondes\n" COLOR_RESET);
    printf("      - Bonus pour le chemin optimal!\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);

    printf("\n");
    printf(COLOR_YELLOW "  >> Generation du labyrinthe...\n" COLOR_RESET);
    generateRandomMaze(&maze);

    findPath(&maze, optimalSolution);
    int optimalLength = strlen(optimalSolution);

    displayMaze(&maze);

    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_WHITE "     Legende:\n" COLOR_RESET);
    printf(COLOR_CYAN "     --------\n" COLOR_RESET);
    printf("      " COLOR_GREEN "S" COLOR_RESET " = Depart     " COLOR_YELLOW "E" COLOR_RESET " = Arrivee     " COLOR_RED "#" COLOR_RESET " = Mur     " COLOR_WHITE "." COLOR_RESET " = Libre\n");
    printf("      " COLOR_GREEN "*" COLOR_RESET " = Chemin correct     " COLOR_RED "X" COLOR_RESET " = Chemin incorrect\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    
    printf("\n");
    printf(COLOR_YELLOW "     Chemin optimal: " COLOR_GREEN "%d" COLOR_RESET " mouvements\n", optimalLength);
    printf("\n");

    time_t startTime = time(NULL);

    printf(COLOR_BOLD "  >> Le chronometre demarre MAINTENANT!\n" COLOR_RESET);
    printf(COLOR_CYAN "  >> Entrez votre chemin: " COLOR_RESET);

    if (fgets(userPath, MAX_PATH_LENGTH, stdin) == NULL) {
        displayFeedback("Erreur de lecture!", 0);
        waitForEnter();
        return;
    }

    time_t endTime = time(NULL);
    int timeUsed = (int)difftime(endTime, startTime);

    userPath[strcspn(userPath, "\n")] = 0;

    for (int i = 0; userPath[i]; i++) {
        userPath[i] = toupper(userPath[i]);
    }

    printf("\n");
    printf(COLOR_YELLOW "     Temps utilise: " COLOR_RESET "%d secondes", timeUsed);
    if (timeUsed <= 30) {
        printf(COLOR_GREEN " - RAPIDE!" COLOR_RESET);
    } else if (timeUsed <= 45) {
        printf(COLOR_YELLOW " - Bien!" COLOR_RESET);
    }
    printf("\n\n");

    if (timeUsed > TIME_LIMIT) {
        displayFeedback("Temps ecoule! Vous avez depasse les 60 secondes.", 0);
        
        printf(COLOR_YELLOW "     Solution optimale: " COLOR_RESET "%s\n", optimalSolution);
        displayMazeWithPath(&maze, optimalSolution, 1);
        
        printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
        printf(COLOR_RED "     Score: 0 points\n" COLOR_RESET);
        printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
        printf("\n");
        waitForEnter();
        return;
    }

    int isValidPath = validateUserPath(&maze, userPath);
    int userLength = strlen(userPath);
    int isOptimal = (isValidPath && userLength == optimalLength);

    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_BOLD "                    RESULTAT                        \n" COLOR_RESET);
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");

    if (isValidPath) {
        displayFeedback("Votre chemin est VALIDE!", 1);
        displayMazeWithPath(&maze, userPath, 1);

        if (isOptimal) {
            printf(COLOR_GREEN "  ====================================================\n" COLOR_RESET);
            printf(COLOR_BOLD "     CHEMIN OPTIMAL!\n" COLOR_RESET);
            printf(COLOR_GREEN "     Vous avez trouve le meilleur chemin!\n" COLOR_RESET);
            printf(COLOR_GREEN "  ====================================================\n" COLOR_RESET);
            printf("\n");
        } else {
            printf(COLOR_YELLOW "     Statistiques:\n" COLOR_RESET);
            printf(COLOR_CYAN "     -------------\n" COLOR_RESET);
            printf("      Votre chemin:    " COLOR_CYAN "%d" COLOR_RESET " mouvements\n", userLength);
            printf("      Chemin optimal:  " COLOR_GREEN "%d" COLOR_RESET " mouvements\n", optimalLength);
            printf("      Difference:      " COLOR_YELLOW "+%d" COLOR_RESET " mouvements\n", userLength - optimalLength);
            printf("\n");
            printf(COLOR_YELLOW "     Solution optimale: " COLOR_RESET "%s\n", optimalSolution);
            printf("\n");
        }

        int score = calculateScore1(userLength, timeUsed, isOptimal);
        
        printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
        printf(COLOR_GREEN "     Score Final: " COLOR_BOLD "%d" COLOR_RESET COLOR_GREEN " points\n" COLOR_RESET, score);
        printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
        printf("\n");
        
        printf(COLOR_YELLOW "     Rang: " COLOR_RESET);
        if (score >= 900) {
            printf(COLOR_MAGENTA "MAITRE DU LABYRINTHE!\n" COLOR_RESET);
        } else if (score >= 700) {
            printf(COLOR_GREEN "EXPERT\n" COLOR_RESET);
        } else if (score >= 500) {
            printf(COLOR_CYAN "AVANCE\n" COLOR_RESET);
        } else if (score >= 300) {
            printf(COLOR_YELLOW "INTERMEDIAIRE\n" COLOR_RESET);
        } else {
            printf(COLOR_WHITE "DEBUTANT\n" COLOR_RESET);
        }
        printf("\n");

    } else {
        displayFeedback("Votre chemin est INVALIDE!", 0);
        displayMazeWithPath(&maze, userPath, 0);

        printf(COLOR_RED "     Raisons possibles d'echec:\n" COLOR_RESET);
        printf(COLOR_CYAN "     --------------------------\n" COLOR_RESET);
        printf("      - Collision avec un mur (#)\n");
        printf("      - Sorti des limites du labyrinthe\n");
        printf("      - N'a pas atteint l'arrivee (E)\n");
        printf("      - Direction invalide\n");
        printf("\n");

        printf(COLOR_YELLOW "     Solution optimale: " COLOR_RESET "%s\n", optimalSolution);
        displayMazeWithPath(&maze, optimalSolution, 1);
        
        printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
        printf(COLOR_RED "     Score: 0 points\n" COLOR_RESET);
        printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
        printf("\n");
    }

    waitForEnter();
}