#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

int** generate_matrix(int vertices) {
    int** matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        matrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = 0; // Инициализация нулями
        }
    }

    //заполнение матрицы
    for (int i = 0; i < vertices; i++) {
        int edges_count = random_int(0, vertices - 1); // Максимум vertices-1 рёбер
        for (int j = 0; j < edges_count; j++) {
            int target_vertex = random_int(0, vertices - 1);
            if (target_vertex != i) { //исключаем петли
                matrix[i][target_vertex] = 1;
                matrix[target_vertex][i] = 1;
            }
        }
    }

    return matrix;
}

void print_matrix(int** matrix, int vertices, const char* name) {
    printf("\n%s (матрица смежности):\n", name);
    printf("   ");
    for (int i = 0; i < vertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < vertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < vertices; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

//преобразование в список
int** matrix_to_list(int** matrix, int vertices, int* list_sizes) {
    int** adj_list = (int**)malloc(vertices * sizeof(int*));

    for (int i = 0; i < vertices; i++) {
        //считаем количество соседей
        int neighbors_count = 0;
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) {
                neighbors_count++;
            }
        }

        adj_list[i] = (int*)malloc(neighbors_count * sizeof(int));
        list_sizes[i] = neighbors_count;


        int index = 0;
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) {
                adj_list[i][index++] = j;
            }
        }
    }

    return adj_list;
}

//вывод списка
void print_list(int** adj_list, int* list_sizes, int vertices, const char* name) {
    printf("\n%s (список смежности):\n", name);
    for (int i = 0; i < vertices; i++) {
        printf("Вершина %d: ", i);
        if (list_sizes[i] == 0) {
            printf("нет соседей");
        }
        else {
            for (int j = 0; j < list_sizes[i]; j++) {
                printf("%d", adj_list[i][j]);
                if (j < list_sizes[i] - 1) {
                    printf(", ");
                }
            }
        }
        printf("\n");
    }
}

void free_matrix(int** matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void free_list(int** adj_list, int* list_sizes, int vertices) {
    for (int i = 0; i < vertices; i++) {
        free(adj_list[i]);
    }
    free(adj_list);
    free(list_sizes);
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");

    int vertices;
    printf("Введите количество вершин графа: ");
    scanf("%d", &vertices);

    if (vertices <= 0) {
        printf("Ошибка: количество вершин должно быть положительным числом!\n");
        return 1;
    }

    //генерация
    int** M1 = generate_matrix(vertices);
    int** M2 = generate_matrix(vertices);

    //вывод
    print_matrix(M1, vertices, "Граф G1");
    print_matrix(M2, vertices, "Граф G2");

    //списки
    int* list_sizes1 = (int*)malloc(vertices * sizeof(int));
    int* list_sizes2 = (int*)malloc(vertices * sizeof(int));

    int** adj_list1 = matrix_to_list(M1, vertices, list_sizes1);
    int** adj_list2 = matrix_to_list(M2, vertices, list_sizes2);

    //вывод списков
    print_list(adj_list1, list_sizes1, vertices, "Граф G1");
    print_list(adj_list2, list_sizes2, vertices, "Граф G2");

    free_matrix(M1, vertices);
    free_matrix(M2, vertices);
    free_list(adj_list1, list_sizes1, vertices);
    free_list(adj_list2, list_sizes2, vertices);

    return 0;
}
