#ifndef TRI_ULTIME_H
#define TRI_ULTIME_H
#define MAX_SIZE 100
// Structure pour stocker les résultats d'un algorithme de tri
typedef struct {
    int swaps;          // Nombre de swaps effectués
    int isSorted;       // 1 si le tableau est trié, 0 sinon
    int withinBudget;   // 1 si dans le budget, 0 sinon
    char name[30];      // Nom de l'algorithme
} Result;
// Type de fonction de tri
typedef void (*SortFunction)(int[], int, int*, int*);
// Déclarations des fonctions de tri
void bubbleSort(int arr[], int n, int *swaps, int *sorted);
void selectionSort(int arr[], int n, int *swaps, int *sorted);
void insertionSort(int arr[], int n, int *swaps, int *sorted);
void quickSortHelper(int arr[], int low, int high, int *swaps, int maxSwaps, int *sorted);
// Fonctions d'analyse
Result analyzeSort(SortFunction sortFunc, int arr[], int n, int maxSwaps);
Result analyzeQuickSort(int arr[], int n, int maxSwaps);
void printResults(Result bubble, Result selection, Result insertion, Result quick, int maxSwaps);
// Fonctions utilitaires
int isSortedArray(int arr[], int n);
void copyArray(int dest[], int src[], int n);
// Fonction principale du jeu
void playTriUltime(void);
#endif // TRI_ULTIME_H