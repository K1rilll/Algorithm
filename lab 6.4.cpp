#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

class Graph {
private:
    vector<vector<int>> matrix;
    int vertices;

public:
    // Конструктор
    Graph(int n, bool randomize = false) : vertices(n), matrix(n, vector<int>(n, 0)) {
        if (randomize) {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);

            // Создаем случайные ребра с вероятностью 40%
            for (int i = 0; i < vertices; i++) {
                for (int j = i + 1; j < vertices; j++) {
                    if (dis(gen) < 0.4) {
                        matrix[i][j] = 1;
                        matrix[j][i] = 1;
                    }
                }
            }
        }
    }

    // Добавление ребра
    void addEdge(int v1, int v2) {
        if (v1 >= 0 && v1 < vertices && v2 >= 0 && v2 < vertices && v1 != v2) {
            matrix[v1][v2] = 1;
            matrix[v2][v1] = 1;
        }
    }

    // Получение значения ребра
    int getEdge(int i, int j) const {
        if (i >= 0 && i < vertices && j >= 0 && j < vertices) {
            return matrix[i][j];
        }
        return 0;
    }

    // Получение количества вершин
    int getVerticesCount() const {
        return vertices;
    }

    // Вывод матрицы смежности
    void print(const string& name) const {
        cout << "\n" << name << " (матрица смежности " << vertices << "x" << vertices << "):\n";

        // Заголовок столбцов
        cout << "   ";
        for (int i = 0; i < vertices; i++) {
            cout << setw(2) << i + 1 << " ";
        }
        cout << "\n";

        // Строки матрицы
        for (int i = 0; i < vertices; i++) {
            cout << setw(2) << i + 1 << " ";
            for (int j = 0; j < vertices; j++) {
                cout << setw(2) << matrix[i][j] << " ";
            }
            cout << "\n";
        }

        // Подсчет ребер
        int edgeCount = countEdges();
        cout << "Количество ребер: " << edgeCount << "\n";
    }

    // Подсчет количества ребер
    int countEdges() const {
        int count = 0;
        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (matrix[i][j] == 1) {
                    count++;
                }
            }
        }
        return count;
    }

    // Декартово произведение графов
    static Graph cartesianProduct(const Graph& g1, const Graph& g2) {
        int n1 = g1.vertices;
        int n2 = g2.vertices;
        int resultSize = n1 * n2;

        Graph result(resultSize);

        // Проходим по всем парам вершин
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                for (int k = 0; k < n1; k++) {
                    for (int l = 0; l < n2; l++) {
                        int v1 = i * n2 + j;  // Вершина (i,j) в результате
                        int v2 = k * n2 + l;  // Вершина (k,l) в результате

                        // Правила декартова произведения:
                        // 1. i == k и есть ребро в G2 между j и l
                        // 2. j == l и есть ребро в G1 между i и k
                        if ((i == k && g2.matrix[j][l] == 1) ||
                            (j == l && g1.matrix[i][k] == 1)) {
                            if (v1 != v2) {  // Исключаем петли
                                result.matrix[v1][v2] = 1;
                                result.matrix[v2][v1] = 1;
                            }
                        }
                    }
                }
            }
        }

        return result;
    }

    // Получение имени вершины в декартовом произведении
    static string getVertexName(int vertex, int n2) {
        int i = vertex / n2;  // Индекс в G1
        int j = vertex % n2;  // Индекс в G2
        return "(" + (i + 1) + (j + 1);
    }
};


// Функция для вывода графа с понятными именами вершин
void printCartesianResult(const Graph& graph, int n2, const string& name) {
    int vertices = graph.getVerticesCount();
    cout << "\n" << name << ":\n";
    cout << "Формат вершин: (номер_в_G1, номер_в_G2)\n";
    cout << "Список смежности:\n";

    for (int i = 0; i < vertices; i++) {
        string vertexName = Graph::getVertexName(i, n2);
        cout << vertexName << ": ";

        bool hasNeighbors = false;
        for (int j = 0; j < vertices; j++) {
            if (graph.getEdge(i, j) == 1 && i != j) {
                if (hasNeighbors) cout << ", ";
                cout << Graph::getVertexName(j, n2);
                hasNeighbors = true;
            }
        }

        if (!hasNeighbors) {
            cout << "нет соседей";
        }
        cout << "\n";
    }
}

int main() {
    // Установка локали для русского языка
    setlocale(LC_ALL, "rus");

    cout << "=== ДЕКАРТОВО ПРОИЗВЕДЕНИЕ ГРАФОВ ===\n\n";

    int n1, n2;

    // Ввод размеров графов
    cout << "Введите количество вершин в графе G1: ";
    cin >> n1;
    cout << "Введите количество вершин в графе G2: ";
    cin >> n2;

    if (n1 <= 0 || n2 <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!\n";
        return 1;
    }

    // Создание случайных графов
    cout << "\nСоздание графов со случайными ребрами...\n";
    Graph g1(n1, true);
    Graph g2(n2, true);

    // Вывод исходных графов
    g1.print("Граф G1");
    g2.print("Граф G2");

    // Выполнение декартова произведения
    cout << "\n=== ВЫПОЛНЕНИЕ ДЕКАРТОВА ПРОИЗВЕДЕНИЯ ===\n";

    Graph result = Graph::cartesianProduct(g1, g2);

    // Вывод результатов
    result.print("Результат G1 X G2 (матрица смежности)");

    return 0;
}
