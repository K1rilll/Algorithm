#include <iostream>
#include <locale.h>
#include <time.h>
#include <cstdio>
#include <queue>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

// Функция для вычисления расстояний (работает для обоих типов графов)
void BFSD(int** G, int numG, int** GD, bool directed) {
    for (int s = 0; s < numG; s++) {
        for (int i = 0; i < numG; i++) {
            GD[s][i] = INT_MAX;
        }
        GD[s][s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int i = 0; i < numG; i++) {
                if (G[v][i] > 0) {
                    if (GD[s][i] > GD[s][v] + G[v][i]) {
                        GD[s][i] = GD[s][v] + G[v][i];
                        q.push(i);
                    }
                }

                // Для ориентированного графа проверяем обратное направление только если неориентированный
                if (!directed && G[i][v] > 0) {
                    if (GD[s][i] > GD[s][v] + G[i][v]) {
                        GD[s][i] = GD[s][v] + G[i][v];
                        q.push(i);
                    }
                }
            }
        }
    }
}

// Функция для генерации графа
void generateGraph(int** G, int numG, bool directed) {
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else if (!directed && j > i) {
                // Для неориентированного генерируем только верхний треугольник
                int value = (rand() % 2 == 0) ? 0 : (rand() % 10 + 1);
                G[i][j] = value;
                G[j][i] = value;
            }
            else if (directed) {
                // Для ориентированного каждая дуга независима
                G[i][j] = (rand() % 2 == 0) ? 0 : (rand() % 10 + 1);
            }
        }
    }
}

// Функция для вывода матрицы
void printMatrix(int** G, int numG, const string& title) {
    cout << title << ":" << endl;
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d ", G[i][j]);
        }
        printf("\n");
    }
}

// Функция для анализа графа
void analyzeGraph(int** G, int numG, bool directed) {
    // Матрица расстояний
    int** GD = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        GD[i] = (int*)malloc(numG * sizeof(int));
    }

    // Эксцентриситеты вершин
    int* Ecc = (int*)malloc(numG * sizeof(int));
    for (int i = 0; i < numG; i++) {
        Ecc[i] = 0;
    }

    // Вычисляем расстояния
    BFSD(G, numG, GD, directed);

    // Выводим матрицу расстояний
    cout << "\nМатрица расстояний:" << endl;
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (GD[i][j] == INT_MAX) {
                printf("%3s ", "∞");
            }
            else {
                printf("%3d ", GD[i][j]);
            }
            if (GD[i][j] != INT_MAX && Ecc[i] < GD[i][j]) {
                Ecc[i] = GD[i][j];
            }
        }
        printf("\n");
    }

    // Вычисляем эксцентриситеты
    cout << "\nЭксцентриситеты вершин:" << endl;
    int r = INT_MAX;
    int d = -1;
    bool disconnected = false;

    for (int i = 0; i < numG; i++) {
        // Проверяем, достижимы ли все вершины из текущей
        bool reachable = true;
        for (int j = 0; j < numG; j++) {
            if (i != j && GD[i][j] == INT_MAX) {
                reachable = false;
                break;
            }
        }

        if (!reachable) {
            disconnected = true;
            cout << "Вершина " << i << ": недостижимы все вершины" << endl;
        }
        else {
            cout << "Вершина " << i << ": " << Ecc[i] << endl;
            if (Ecc[i] > 0) {
                r = (r > Ecc[i]) ? Ecc[i] : r;
                d = (d < Ecc[i]) ? Ecc[i] : d;
            }
        }
    }

    if (disconnected) {
        cout << "\nГраф несвязный!" << endl;


        // Для несвязного графа радиус и диаметр не определены
        // Но можно найти в каждой компоненте связности
        cout << "Для несвязного графа радиус и диаметр не определены." << endl;

        // Находим центральные и периферийные вершины в их компонентах
        vector<int> central_vertices;
        vector<int> peripheral_vertices;

        // Простой алгоритм для нахождения компонент связности
        bool* visited = new bool[numG] {false};

        for (int i = 0; i < numG; i++) {
            if (!visited[i]) {
                // Находим компоненту, содержащую вершину i
                vector<int> component;
                queue<int> q;
                q.push(i);
                visited[i] = true;

                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    component.push_back(v);

                    for (int j = 0; j < numG; j++) {
                        if (!visited[j] && ((G[v][j] > 0) || (!directed && G[j][v] > 0))) {
                            visited[j] = true;
                            q.push(j);
                        }
                    }
                }

                if (component.size() > 1) {
                    // Находим эксцентриситеты в компоненте
                    int comp_r = INT_MAX;
                    int comp_d = -1;
                    vector<int> comp_ecc(component.size(), 0);

                    for (int k = 0; k < component.size(); k++) {
                        int v = component[k];
                        int max_dist = 0;
                        for (int m = 0; m < component.size(); m++) {
                            int u = component[m];
                            if (v != u && GD[v][u] > max_dist) {
                                max_dist = GD[v][u];
                            }
                        }
                        comp_ecc[k] = max_dist;
                        if (max_dist > 0) {
                            comp_r = min(comp_r, max_dist);
                            comp_d = max(comp_d, max_dist);
                        }
                    }

                    // Находим центральные и периферийные вершины в компоненте
                    for (int k = 0; k < component.size(); k++) {
                        if (comp_ecc[k] == comp_r && comp_r != INT_MAX) {
                            central_vertices.push_back(component[k]);
                        }
                        if (comp_ecc[k] == comp_d && comp_d != -1) {
                            peripheral_vertices.push_back(component[k]);
                        }
                    }
                }
                else {
                    // Изолированная вершина
                    central_vertices.push_back(i);
                    peripheral_vertices.push_back(i);
                }
            }
        }

        delete[] visited;

        // Выводим результаты
        if (!central_vertices.empty()) {
            cout << "\nЦентральные вершины (в своих компонентах): ";
            for (int v : central_vertices) {
                cout << v << " ";
            }
            cout << endl;
        }

        if (!peripheral_vertices.empty()) {
            cout << "Периферийные вершины (в своих компонентах): ";
            for (int v : peripheral_vertices) {
                cout << v << " ";
            }
            cout << endl;
        }

    }
    else {
        // Для связного графа
        cout << "\nРадиус графа: " << r << endl;
        cout << "Диаметр графа: " << d << endl;

        // Находим центральные и периферийные вершины
        vector<int> central_vertices;
        vector<int> peripheral_vertices;

        for (int i = 0; i < numG; i++) {
            if (Ecc[i] == r) {
                central_vertices.push_back(i);
            }
            if (Ecc[i] == d) {
                peripheral_vertices.push_back(i);
            }
        }

        cout << "\nЦентральные вершины: ";
        for (int v : central_vertices) {
            cout << v << " ";
        }
        cout << endl;


        cout << "Периферийные вершины: ";
        for (int v : peripheral_vertices) {
            cout << v << " ";
        }
        cout << endl;
    }

    // Освобождаем память
    for (int i = 0; i < numG; i++) {
        free(GD[i]);
    }
    free(GD);
    free(Ecc);
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");

    int numG;
    cout << "Введите количество вершин: " << endl;
    cin >> numG;

    // Создаем графы
    int** G_undirected = (int**)malloc(numG * sizeof(int*));
    int** G_directed = (int**)malloc(numG * sizeof(int*));

    for (int i = 0; i < numG; i++) {
        G_undirected[i] = (int*)malloc(numG * sizeof(int));
        G_directed[i] = (int*)malloc(numG * sizeof(int));
    }

    // Генерируем неориентированный граф
    cout << "\n=== НЕОРИЕНТИРОВАННЫЙ ГРАФ ===" << endl;
    generateGraph(G_undirected, numG, false);
    printMatrix(G_undirected, numG, "Матрица смежности (неориентированный)");
    analyzeGraph(G_undirected, numG, false);

    // Генерируем ориентированный граф
    cout << "\n\n=== ОРИЕНТИРОВАННЫЙ ГРАФ ===" << endl;
    generateGraph(G_directed, numG, true);
    printMatrix(G_directed, numG, "Матрица смежности (ориентированный)");
    analyzeGraph(G_directed, numG, true);

    // Освобождаем память
    for (int i = 0; i < numG; i++) {
        free(G_undirected[i]);
        free(G_directed[i]);
    }
    free(G_undirected);
    free(G_directed);

    return 0;
}

