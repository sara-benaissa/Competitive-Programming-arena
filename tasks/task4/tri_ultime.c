#include <stdio.h>
#include <string.h>
#include "tri_ultime.h"
#include "../../common/ui.h"

// Vérifie si un tableau est trié
int isSortedArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// Copie un tableau
void copyArray(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Tri à bulles
void bubbleSort(int arr[], int n, int *swaps, int *sorted) {
    *swaps = 0;
    *sorted = 0;
    
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*swaps)++;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    
    *sorted = isSortedArray(arr, n);
}

// Tri par sélection
void selectionSort(int arr[], int n, int *swaps, int *sorted) {
    *swaps = 0;
    *sorted = 0;
    
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            (*swaps)++;
        }
    }
    
    *sorted = isSortedArray(arr, n);
}

// Tri par insertion
void insertionSort(int arr[], int n, int *swaps, int *sorted) {
    *swaps = 0;
    *sorted = 0;
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            (*swaps)++;
        }
        arr[j + 1] = key;
    }
    
    *sorted = isSortedArray(arr, n);
}

// Fonction de partition pour QuickSort
int partition(int arr[], int low, int high, int *swaps, int maxSwaps) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            if (i != j && *swaps < maxSwaps) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                (*swaps)++;
            }
        }
    }
    
    if (i + 1 != high && *swaps < maxSwaps) {
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        (*swaps)++;
    }
    
    return i + 1;
}

// QuickSort avec limite de swaps
void quickSortHelper(int arr[], int low, int high, int *swaps, int maxSwaps, int *sorted) {
    if (low < high && *swaps < maxSwaps) {
        int pi = partition(arr, low, high, swaps, maxSwaps);
        
        if (*swaps < maxSwaps) {
            quickSortHelper(arr, low, pi - 1, swaps, maxSwaps, sorted);
        }
        if (*swaps < maxSwaps) {
            quickSortHelper(arr, pi + 1, high, swaps, maxSwaps, sorted);
        }
    }
}

// Analyse un algorithme de tri
Result analyzeSort(SortFunction sortFunc, int arr[], int n, int maxSwaps) {
    Result res;
    int tempArr[MAX_SIZE];
    copyArray(tempArr, arr, n);
    
    int swaps = 0;
    int sorted = 0;
    
    sortFunc(tempArr, n, &swaps, &sorted);
    
    res.swaps = swaps;
    res.isSorted = isSortedArray(tempArr, n);
    res.withinBudget = (swaps <= maxSwaps);
    
    return res;
}

// Analyse QuickSort
Result analyzeQuickSort(int arr[], int n, int maxSwaps) {
    Result res;
    int tempArr[MAX_SIZE];
    copyArray(tempArr, arr, n);
    
    int swaps = 0;
    int sorted = 0;
    
    quickSortHelper(tempArr, 0, n - 1, &swaps, maxSwaps, &sorted);
    
    res.swaps = swaps;
    res.isSorted = isSortedArray(tempArr, n);
    res.withinBudget = (swaps <= maxSwaps);
    strcpy(res.name, "QuickSort");
    
    return res;
}

// Affiche les résultats
void printResults(Result bubble, Result selection, Result insertion, Result quick, int maxSwaps) {
    printf("\n");
    printf(COLOR_CYAN "     Resultats de l'Analyse:\n" COLOR_RESET);
    printf(COLOR_CYAN "     ------------------------\n" COLOR_RESET);
    printf("\n");
    
    // Tri à Bulles
    printf(COLOR_YELLOW "     Tri a Bulles:\n" COLOR_RESET);
    printf("      - Swaps: " COLOR_CYAN "%d\n" COLOR_RESET, bubble.swaps);
    printf("      - Trie: %s\n", bubble.isSorted ? COLOR_GREEN "Oui" COLOR_RESET : COLOR_RED "Non" COLOR_RESET);
    printf("      - Dans le budget: %s\n", bubble.withinBudget ? COLOR_GREEN "Oui" COLOR_RESET : COLOR_RED "Non" COLOR_RESET);
    printf("\n");
    
    // Tri par Sélection
    printf(COLOR_YELLOW "     Tri par Selection:\n" COLOR_RESET);
    printf("      - Swaps: " COLOR_CYAN "%d\n" COLOR_RESET, selection.swaps);
    printf("      - Trie: %s\n", selection.isSorted ? COLOR_GREEN "Oui" COLOR_RESET : COLOR_RED "Non" COLOR_RESET);
    printf("      - Dans le budget: %s\n", selection.withinBudget ? COLOR_GREEN "Oui" COLOR_RESET : COLOR_RED "Non" COLOR_RESET);
    printf("\n");
    
    // Tri par Insertion
    printf(COLOR_YELLOW "     Tri par Insertion:\n" COLOR_RESET);
    printf("      - Swaps: " COLOR_CYAN "%d\n" COLOR_RESET, insertion.swaps);
    printf("      - Trie: %s\n", insertion.isSorted ? COLOR_GREEN "Oui" COLOR_RESET : COLOR_RED "Non" COLOR_RESET);
    printf("      - Dans le budget: %s\n", insertion.withinBudget ? COLOR_GREEN "Oui" COLOR_RESET : COLOR_RED "Non" COLOR_RESET);
    printf("\n");
    
    // QuickSort
    printf(COLOR_YELLOW "     QuickSort:\n" COLOR_RESET);
    printf("      - Swaps: " COLOR_CYAN "%d\n" COLOR_RESET, quick.swaps);
    printf("      - Trie: %s\n", quick.isSorted ? COLOR_GREEN "Oui" COLOR_RESET : COLOR_RED "Non" COLOR_RESET);
    printf("      - Dans le budget: %s\n", quick.withinBudget ? COLOR_GREEN "Oui" COLOR_RESET : COLOR_RED "Non" COLOR_RESET);
    printf("\n");
    
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_MAGENTA "     Recommandation: " COLOR_RESET);
    
    if (insertion.withinBudget && insertion.isSorted) {
        printf(COLOR_GREEN "Tri par Insertion\n" COLOR_RESET);
        printf(COLOR_WHITE "     (Efficace pour ce cas)\n" COLOR_RESET);
    } else if (quick.withinBudget && quick.isSorted) {
        printf(COLOR_GREEN "QuickSort\n" COLOR_RESET);
        printf(COLOR_WHITE "     (Meilleur en general)\n" COLOR_RESET);
    } else if (selection.withinBudget && selection.isSorted) {
        printf(COLOR_GREEN "Tri par Selection\n" COLOR_RESET);
    } else if (bubble.withinBudget && bubble.isSorted) {
        printf(COLOR_GREEN "Tri a Bulles\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "Aucun\n" COLOR_RESET);
        printf(COLOR_WHITE "     (Budget insuffisant pour trier completement)\n" COLOR_RESET);
    }
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");
}

void playTriUltime() {
    int n;
    int arr[MAX_SIZE];
    int maxSwaps;
    
    displayWelcome("Tri Ultime");
    
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_YELLOW "     Regles du Jeu:\n" COLOR_RESET);
    printf(COLOR_CYAN "     --------------\n" COLOR_RESET);
    printf("      - Analysez les algorithmes de tri\n");
    printf("      - Comparez leur efficacite\n");
    printf("      - Trouvez le meilleur avec un budget de swaps\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");
    
    printf(COLOR_YELLOW "  >> Entrez la taille du tableau (1-%d): " COLOR_RESET, MAX_SIZE);
    if (scanf("%d", &n) != 1) {
        while(getchar() != '\n');
        displayFeedback("Erreur de saisie!", 0);
        waitForEnter();
        return;
    }
    
    if (n <= 0 || n > MAX_SIZE) {
        displayFeedback("Taille invalide!", 0);
        waitForEnter();
        return;
    }
    
    printf("\n");
    printf(COLOR_YELLOW "     Entrez les %d elements:\n" COLOR_RESET, n);
    for (int i = 0; i < n; i++) {
        printf(COLOR_CYAN "      Element %d: " COLOR_RESET, i + 1);
        if (scanf("%d", &arr[i]) != 1) {
            while(getchar() != '\n');
            displayFeedback("Erreur de saisie!", 0);
            waitForEnter();
            return;
        }
    }
    
    printf("\n");
    printf(COLOR_YELLOW "  >> Budget maximum de swaps: " COLOR_RESET);
    if (scanf("%d", &maxSwaps) != 1) {
        while(getchar() != '\n');
        displayFeedback("Erreur de saisie!", 0);
        waitForEnter();
        return;
    }
    
    if (maxSwaps < 0) {
        displayFeedback("Le nombre de swaps doit etre positif!", 0);
        waitForEnter();
        return;
    }
    
    printf("\n");
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_WHITE "     Tableau: " COLOR_RESET);
    for (int i = 0; i < n; i++) {
        printf(COLOR_CYAN "%d" COLOR_RESET, arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
    printf(COLOR_WHITE "     Budget: " COLOR_GREEN "%d" COLOR_RESET " swaps maximum\n", maxSwaps);
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf("\n");
    
    printf(COLOR_YELLOW "  >> Analyse en cours...\n" COLOR_RESET);
    printf("\n");
    
    Result rBubble = analyzeSort(bubbleSort, arr, n, maxSwaps);
    Result rSelect = analyzeSort(selectionSort, arr, n, maxSwaps);
    Result rInsert = analyzeSort(insertionSort, arr, n, maxSwaps);
    Result rQuick  = analyzeQuickSort(arr, n, maxSwaps);
    
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    printf(COLOR_BOLD "                    RESULTATS                        \n" COLOR_RESET);
    printf(COLOR_CYAN "  ====================================================\n" COLOR_RESET);
    
    printResults(rBubble, rSelect, rInsert, rQuick, maxSwaps);
    
    waitForEnter();
}