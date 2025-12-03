#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <random>

using namespace std;

class GraphMatrix {
private:
    vector<vector<int>> matrix;
    int vertices;

public:
    GraphMatrix(int n) : vertices(n), matrix(n, vector<int>(n, 0)) {
        // Автоматическое создание рёбер с вероятностью 50%
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);

        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (dis(gen) < 0.5) { // 50% вероятность
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                }
            }
        }
    }

    void addEdge(int v1, int v2) {
        if (v1 >= 0 && v1 < vertices && v2 >= 0 && v2 < vertices && v1 != v2) {
            matrix[v1][v2] = 1;
            matrix[v2][v1] = 1;
        }
    }

    void print(const string& name) {
        cout << "\n" << name << " (матрица смежности " << vertices << "x" << vertices << "):\n";
        cout << "   ";
        for (int i = 0; i < vertices; i++) {
            cout << setw(2) << i + 1 << " ";
        }
        cout << "\n";

        for (int i = 0; i < vertices; i++) {
            cout << setw(2) << i + 1 << " ";
            for (int j = 0; j < vertices; j++) {
                cout << setw(2) << matrix[i][j] << " ";
            }
            cout << "\n";
        }
    }

    // а) Отождествление вершин
    void identifyVertices(int v1, int v2) {
        if (!isValidVertex(v1) || !isValidVertex(v2) || v1 == v2) {
            cout << "Ошибка: неверные номера вершин!\n";
            return;
        }

        // Сохраняем вершину с меньшим номером, удаляем большую
        int keep = min(v1, v2);
        int remove = max(v1, v2);

        // Объединяем связи: keep получает все связи remove
        for (int i = 0; i < vertices; i++) {
            if (matrix[remove][i] == 1 && i != keep) {
                matrix[keep][i] = 1;
                matrix[i][keep] = 1;
            }
        }

        // Удаляем строку и столбец remove
        matrix.erase(matrix.begin() + remove);
        for (auto& row : matrix) {
            row.erase(row.begin() + remove);
        }

        vertices--;
        cout << "Вершины " << v1 + 1 << " и " << v2 + 1 << " отождествлены.\n";
    }

    // б) Стягивание ребра
    void contractEdge(int v1, int v2) {
        if (!isValidVertex(v1) || !isValidVertex(v2) || v1 == v2) {
            cout << "Ошибка: неверные номера вершин!\n";
            return;
        }

        if (matrix[v1][v2] == 0) {
            cout << "Ошибка: вершины " << v1 + 1 << " и " << v2 + 1 << " не соединены ребром!\n";
            return;
        }

        identifyVertices(v1, v2);
        cout << "Ребро между вершинами " << v1 + 1 << " и " << v2 + 1 << " стянуто.\n";
    }

    // в) Расщепление вершины
    void splitVertex(int v) {
        if (!isValidVertex(v)) {
            cout << "Ошибка: неверный номер вершины!\n";
            return;
        }

        // Добавляем новую строку и столбец
        for (auto& row : matrix) {
            row.push_back(0);
        }
        matrix.push_back(vector<int>(vertices + 1, 0));

        // Новая вершина
        int newVertex = vertices;

        // Переносим часть связей на новую вершину
        vector<int> connections;
        for (int i = 0; i < vertices; i++) {
            if (matrix[v][i] == 1 && i != v) {
                connections.push_back(i);
            }
        }

        // Переносим примерно половину связей
        for (size_t i = 0; i < connections.size(); i++) {
            if (i % 2 == 0) { // простой критерий для демонстрации
                int neighbor = connections[i];
                matrix[newVertex][neighbor] = 1;
                matrix[neighbor][newVertex] = 1;
                matrix[v][neighbor] = 0;
                matrix[neighbor][v] = 0;
            }
        }

        // Связываем новую вершину с исходной
        matrix[v][newVertex] = 1;
        matrix[newVertex][v] = 1;


        vertices++;
        cout << "Вершина " << v + 1 << " расщеплена на вершины " << v + 1 << " и " << newVertex + 1 << ".\n";
    }

    bool isValidVertex(int v) {
        return v >= 0 && v < vertices;
    }

    int getVerticesCount() { return vertices; }
};

class GraphList {
private:
    vector<vector<int>> adjList;
    int vertices;

public:
    GraphList(int n) : vertices(n), adjList(n) {
        // Автоматическое создание рёбер с вероятностью 50%
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);

        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (dis(gen) < 0.5) { // 50% вероятность
                    // Проверяем, нет ли уже такого ребра
                    if (find(adjList[i].begin(), adjList[i].end(), j) == adjList[i].end()) {
                        adjList[i].push_back(j);
                    }
                    if (find(adjList[j].begin(), adjList[j].end(), i) == adjList[j].end()) {
                        adjList[j].push_back(i);
                    }
                }
            }
        }
    }

    void addEdge(int v1, int v2) {
        if (v1 >= 0 && v1 < vertices && v2 >= 0 && v2 < vertices && v1 != v2) {
            // Проверяем, нет ли уже такого ребра
            if (find(adjList[v1].begin(), adjList[v1].end(), v2) == adjList[v1].end()) {
                adjList[v1].push_back(v2);
            }
            if (find(adjList[v2].begin(), adjList[v2].end(), v1) == adjList[v2].end()) {
                adjList[v2].push_back(v1);
            }
        }
    }

    void print(const string& name) {
        cout << "\n" << name << " (списки смежности):\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Вершина " << i + 1 << ": ";
            if (adjList[i].empty()) {
                cout << "нет соседей";
            }
            else {
                for (size_t j = 0; j < adjList[i].size(); j++) {
                    cout << adjList[i][j] + 1;
                    if (j < adjList[i].size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << "\n";
        }
    }

    // а) Отождествление вершин
    void identifyVertices(int v1, int v2) {
        if (!isValidVertex(v1) || !isValidVertex(v2) || v1 == v2) {
            cout << "Ошибка: неверные номера вершин!\n";
            return;
        }

        int keep = min(v1, v2);
        int remove = max(v1, v2);

        // Объединяем списки смежности
        for (int neighbor : adjList[remove]) {
            if (neighbor != keep && find(adjList[keep].begin(), adjList[keep].end(), neighbor) == adjList[keep].end()) {
                adjList[keep].push_back(neighbor);
            }
        }

        // Обновляем ссылки у всех соседей remove
        for (int i = 0; i < vertices; i++) {
            if (i != remove) {
                auto it = find(adjList[i].begin(), adjList[i].end(), remove);
                if (it != adjList[i].end()) {
                    adjList[i].erase(it);
                    if (i != keep && find(adjList[i].begin(), adjList[i].end(), keep) == adjList[i].end()) {
                        adjList[i].push_back(keep);
                    }
                }
            }
        }

        // Удаляем вершину remove
        adjList.erase(adjList.begin() + remove);

        // Обновляем номера вершин в списках
        for (auto& list : adjList) {
            for (int& neighbor : list) {
                if (neighbor > remove) {
                    neighbor--;
                }
            }
        }

        vertices--;
        cout << "Вершины " << v1 + 1 << " и " << v2 + 1 << " отождествлены.\n";
    }

    // б) Стягивание ребра
    void contractEdge(int v1, int v2) {
        if (!isValidVertex(v1) || !isValidVertex(v2) || v1 == v2) {
            cout << "Ошибка: неверные номера вершин!\n";
            return;
        }


        if (find(adjList[v1].begin(), adjList[v1].end(), v2) == adjList[v1].end()) {
            cout << "Ошибка: вершины " << v1 + 1 << " и " << v2 + 1 << " не соединены ребром!\n";
            return;
        }

        identifyVertices(v1, v2);
        cout << "Ребро между вершинами " << v1 + 1 << " и " << v2 + 1 << " стянуто.\n";
    }

    // в) Расщепление вершины
    void splitVertex(int v) {
        if (!isValidVertex(v)) {
            cout << "Ошибка: неверный номер вершины!\n";
            return;
        }

        // Добавляем новую вершину
        adjList.push_back(vector<int>());
        int newVertex = vertices;

        // Переносим часть связей на новую вершину
        vector<int> connections = adjList[v];
        for (size_t i = 0; i < connections.size(); i++) {
            if (i % 2 == 0) { // простой критерий для демонстрации
                int neighbor = connections[i];

                // Удаляем связь v-neighbor
                auto it = find(adjList[v].begin(), adjList[v].end(), neighbor);
                if (it != adjList[v].end()) {
                    adjList[v].erase(it);
                }

                // Удаляем связь neighbor-v
                it = find(adjList[neighbor].begin(), adjList[neighbor].end(), v);
                if (it != adjList[neighbor].end()) {
                    adjList[neighbor].erase(it);
                }

                // Добавляем связь newVertex-neighbor
                adjList[newVertex].push_back(neighbor);
                adjList[neighbor].push_back(newVertex);
            }
        }

        // Связываем новую вершину с исходной
        adjList[v].push_back(newVertex);
        adjList[newVertex].push_back(v);

        vertices++;
        cout << "Вершина " << v + 1 << " расщеплена на вершины " << v + 1 << " и " << newVertex + 1 << ".\n";
    }

    bool isValidVertex(int v) {
        return v >= 0 && v < vertices;
    }

    int getVerticesCount() { return vertices; }
};

int main() {
    setlocale(LC_ALL, "rus");

    int representation, vertices, choice;

    cout << "=== ОПЕРАЦИИ НАД ГРАФАМИ ===\n";

    cout << "Выберите представление графа:\n";
    cout << "1 - Матричное представление\n";
    cout << "2 - Списки смежности\n";
    cout << "Ваш выбор: ";
    cin >> representation;

    cout << "Введите количество вершин: ";
    cin >> vertices;

    if (vertices <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным числом!\n";
        return 1;
    }

    if (representation == 1) {
        GraphMatrix graph(vertices);
        cout << "Создан граф с " << vertices << " вершинами и случайными рёбрами (вероятность 50%).\n";
        graph.print("Исходный граф");

        do {
            cout << "\nОперации:\n";
            cout << "1 - Добавить ребро\n";
            cout << "2 - Отождествить вершины\n";
            cout << "3 - Стянуть ребро\n";
            cout << "4 - Расщепить вершину\n";
            cout << "5 - Показать граф\n";
            cout << "0 - Выход\n";
            cout << "Ваш выбор: ";
            cin >> choice;


            int v1, v2;
            switch (choice) {
            case 1:
                cout << "Введите вершины ребра (v1 v2): ";
                cin >> v1 >> v2;
                graph.addEdge(v1 - 1, v2 - 1);
                break;
            case 2:
                cout << "Введите вершины для отождествления (v1 v2): ";
                cin >> v1 >> v2;
                graph.identifyVertices(v1 - 1, v2 - 1);
                graph.print("Граф после отождествления");
                break;
            case 3:
                cout << "Введите вершины ребра для стягивания (v1 v2): ";
                cin >> v1 >> v2;
                graph.contractEdge(v1 - 1, v2 - 1);
                graph.print("Граф после стягивания");
                break;
            case 4:
                cout << "Введите вершину для расщепления: ";
                cin >> v1;
                graph.splitVertex(v1 - 1);
                graph.print("Граф после расщепления");
                break;
            case 5:
                graph.print("Текущий граф");
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор!\n";
            }
        } while (choice != 0);

    }
    else {
        GraphList graph(vertices);
        cout << "Создан граф с " << vertices << " вершинами и случайными рёбрами.\n";
        graph.print("Исходный граф");

        do {
            cout << "\nОперации:\n";
            cout << "1 - Добавить ребро\n";
            cout << "2 - Отождествить вершины\n";
            cout << "3 - Стянуть ребро\n";
            cout << "4 - Расщепить вершину\n";
            cout << "5 - Показать граф\n";
            cout << "0 - Выход\n";
            cout << "Ваш выбор: ";
            cin >> choice;

            int v1, v2;
            switch (choice) {
            case 1:
                cout << "Введите вершины ребра (v1 v2): ";
                cin >> v1 >> v2;
                graph.addEdge(v1 - 1, v2 - 1);
                break;
            case 2:
                cout << "Введите вершины для отождествления (v1 v2): ";
                cin >> v1 >> v2;
                graph.identifyVertices(v1 - 1, v2 - 1);
                graph.print("Граф после отождествления");
                break;
            case 3:
                cout << "Введите вершины ребра для стягивания (v1 v2): ";
                cin >> v1 >> v2;
                graph.contractEdge(v1 - 1, v2 - 1);
                graph.print("Граф после стягивания");
                break;
            case 4:
                cout << "Введите вершину для расщепления: ";
                cin >> v1;
                graph.splitVertex(v1 - 1);
                graph.print("Граф после расщепления");
                break;
            case 5:
                graph.print("Текущий граф");
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор!\n";
            }
        } while (choice != 0);
    }

    return 0;
}
