#ifndef COURSE_ROBOTS_H
#define COURSE_ROBOTS_H

// ==================== CONSTANTES ====================

// Taille du labyrinthe
#define MAZE_SIZE 8

// Limites du jeu
#define MAX_PATH_LENGTH 200
#define TIME_LIMIT 60

// Symboles pour afficher le labyrinthe
#define EMPTY '.'
#define WALL '#'
#define START 'S'
#define END 'E'
#define PATH '*'
#define WRONG 'X'

// ==================== STRUCTURES ====================

// Structure pour une position (x, y)
typedef struct {
    int x;
    int y;
} Position;

// Structure pour le labyrinthe
typedef struct {
    char grid[MAZE_SIZE][MAZE_SIZE];
    Position start;
    Position end;
} Maze;

// Structure pour la file d'attente (queue) utilisée dans BFS
typedef struct {
    Position positions[MAZE_SIZE * MAZE_SIZE];
    int front;
    int rear;
} Queue;

// ==================== FONCTIONS DE LA QUEUE ====================

void initQueue(Queue* q);
void enqueue(Queue* q, Position pos);
Position dequeue(Queue* q);
int isQueueEmpty(Queue* q);

// ==================== GÉNÉRATION DU LABYRINTHE ====================

void initEmptyMaze(Maze* maze);
void generateRandomMaze(Maze* maze);

// ==================== AFFICHAGE ====================

void displayMaze(Maze* maze);
void displayMazeWithPath(Maze* maze, const char* path, int isCorrect);

// ==================== VALIDATION ====================

int isValid(Maze* maze, Position pos, int visited[MAZE_SIZE][MAZE_SIZE]);
int validateUserPath(Maze* maze, const char* userPath);

// ==================== ALGORITHME BFS ====================

void reconstructPath(Maze* maze, Position parent[MAZE_SIZE][MAZE_SIZE], char* solution);
int findPath(Maze* maze, char* solution);

// ==================== SCORING ====================

int calculateScore1(int pathLength, int timeUsed, int isOptimal);

// ==================== FONCTION PRINCIPALE ====================

void playCourseRobots();

#endif // COURSE_ROBOTS_H