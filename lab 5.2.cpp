#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Функция для генерации матрицы
int** generateIncidenceMatrix(int n, int* edge_count) {
   
    int** adj_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        adj_matrix[i] = (int*)calloc(n, sizeof(int));
    }
    *edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2 == 1) {
                adj_matrix[i][j] = 1;
                adj_matrix[j][i] = 1;
                (*edge_count)++;
            }
        }
    }

    // Создаем матрицу инцидентности
    int** inc_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        inc_matrix[i] = (int*)calloc(*edge_count, sizeof(int));
    }

    // Заполняем
    int edge_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj_matrix[i][j] == 1) {
                inc_matrix[i][edge_index] = 1;
                inc_matrix[j][edge_index] = 1;
                edge_index++;
            }
        }
    }

    // Освобождаем
    for (int i = 0; i < n; i++) {
        free(adj_matrix[i]);
    }
    free(adj_matrix);

    return inc_matrix;
}

void printIncidenceMatrix(int n, int edge_count, int** matrix) {
    printf("Матрица инцидентности:\n   ");
    for (int j = 0; j < edge_count; j++) {
        printf("e%-2d", j + 1);  
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("v%-2d", i + 1); 
        for (int j = 0; j < edge_count; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int calculateDegree(int n, int edge_count, int** matrix, int vertex) {
    int degree = 0;
    for (int j = 0; j < edge_count; j++) {
        degree += matrix[vertex][j];
    }
    return degree;
}


int graphSize(int edge_count) {
    return edge_count;
}

void findIsolatedVertices(int n, int edge_count, int** matrix) {
    printf("Изолированные вершины (степень 0): ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (calculateDegree(n, edge_count, matrix, i) == 0) {
            printf("%d ", i + 1); 
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

void findEndVertices(int n, int edge_count, int** matrix) {
    printf("Концевые вершины (степень 1): ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (calculateDegree(n, edge_count, matrix, i) == 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}
void findDominatingVertices(int n, int edge_count, int** matrix) {
    printf("Доминирующие вершины (степень %d): ", n - 1);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (calculateDegree(n, edge_count, matrix, i) == n - 1) {
            printf("%d ", i + 1); 
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

void printVertexDegrees(int n, int edge_count, int** matrix) {
    printf("Степени вершин:\n");
    for (int i = 0; i < n; i++) {
        printf("Вершина %d: степень %d\n", i + 1, calculateDegree(n, edge_count, matrix, i));
    }
}

int main() {
    srand(time(NULL)); 
    setlocale(LC_ALL, "rus");

    int n; 
    int edge_count; 

    printf("Введите количество вершин графа: ");
    scanf_s("%d", &n);

    int** inc_matrix = generateIncidenceMatrix(n, &edge_count);

    printf("\n");
    printIncidenceMatrix(n, edge_count, inc_matrix);

    int size = graphSize(edge_count);
    printf("\nРазмер графа (количество ребер): %d\n", size);

    printf("\n");
    printVertexDegrees(n, edge_count, inc_matrix);

    printf("\n");
    findIsolatedVertices(n, edge_count, inc_matrix);
    findEndVertices(n, edge_count, inc_matrix);
    findDominatingVertices(n, edge_count, inc_matrix);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(inc_matrix[i]);
    }
    free(inc_matrix);

    return 0;
}