#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

//функция для генерации матрицы
void generateMatrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {

            if (rand() % 2 == 1) {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }
    }   
}

//функция для вывода
void printMatrix(int n, int** matrix) {
    printf("Матрица смежности:\n   ");
    for (int i = 0; i < n; i++) {
        printf("%2d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int calculateDegree(int n, int** matrix, int vertex) {
    int degree = 0;
    for (int i = 0; i < n; i++) {
        if (i == vertex) {
            degree += matrix[vertex][i] * 2;
        }
        else {
            degree += matrix[vertex][i];
        }
    }
    return degree;
}


int calculateSimpleDegree(int n, int** matrix, int vertex) {
    int degree = 0;
    for (int i = 0; i < n; i++) {
        if (i != vertex) {
            degree += matrix[vertex][i];
        }
    }
    return degree;
}

//определение размера графа
int graphSize(int n, int** matrix) {
    int edges = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                edges += matrix[i][j];
            }
            else {
                edges += matrix[i][j];
            }
        }
    }
    return edges;
}

//изолированные вершины
void findIsolated(int n, int** matrix) {
    printf("Изолированные вершины (степень 0): ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (calculateDegree(n, matrix, i) == 0) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

//концевые вершины
void findEnd(int n, int** matrix) {
    printf("Концевые вершины: ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        int simple_degree = calculateSimpleDegree(n, matrix, i);
        int loop = matrix[i][i];

        if ((simple_degree == 1 && !loop) ||
            (simple_degree == 1 && loop)) {
            printf("%d", i + 1);
            
            printf(" ");
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

//доминирующие вершины 
void findDominating(int n, int** matrix) {
    printf("Доминирующие вершины (соединены со всеми остальными): ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        int simple_degree = calculateSimpleDegree(n, matrix, i);
        int loop = matrix[i][i];

        if (simple_degree == n - 1) {
            printf("%d", i + 1);
            if (loop) {
                printf("(с петлей)");
            }
            printf(" ");
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

//функция для вывода степеней вершин
void printDegrees(int n, int** matrix) {
    printf("Степени вершин:\n");
    for (int i = 0; i < n; i++) {
        int degree_with_loops = calculateDegree(n, matrix, i);
        int simple_degree = calculateSimpleDegree(n, matrix, i);
        printf("Вершина %d: степень %d", i + 1, degree_with_loops);
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");

    int n;

    printf("Введите количество вершин графа: ");
    scanf_s("%d", &n);

    // выделение памяти 
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }

    generateMatrix(n, matrix);

    printf("\n");
    printMatrix(n, matrix);

    int size = graphSize(n, matrix);
    printf("\nРазмер графа (количество ребер): %d\n", size);

    printf("\n");
    printDegrees(n, matrix);

    printf("\n");
    findIsolated(n, matrix);
    findEnd(n, matrix);
    findDominating(n, matrix);



    //освобождение памяти
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}