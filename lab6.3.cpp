#include <iostream>
#include <vector>
#include <iomanip>
#include <locale>
#include <random>

using namespace std;

class GraphMatrix {
private:
    vector<vector<int>> matrix;
    int vertices;

public:
    // Конструктор со случайным заполнением
    GraphMatrix(int n) : vertices(n), matrix(n, vector<int>(n, 0)) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                // Для петель (i == j) и рёбер (i != j) вероятность 50%
                if (dis(gen) < 0.5) {
                    matrix[i][j] = 1;
                    // Для неориентированного графа симметрично
                    if (i != j) {
                        matrix[j][i] = 1;
                    }
                }
            }
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

        // Подсчет петель и рёбер для информации
        int loops = 0;
        int edges = 0;
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (matrix[i][j] == 1) {
                    if (i == j) {
                        loops++;
                    }
                    else if (i < j) { // Считаем каждое ребро только один раз
                        edges++;
                    }
                }
            }
        }
        cout << "Петли: " << loops << ", Рёбра: " << edges << "\n";
    }

    // а) Объединение графов G = G1 ∪ G2
    static GraphMatrix unionGraphs(const GraphMatrix& g1, const GraphMatrix& g2) {
        if (g1.vertices != g2.vertices) {
            throw invalid_argument("Графы должны иметь одинаковое количество вершин!");
        }

        int n = g1.vertices;
        GraphMatrix result(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Объединение: ребро есть, если оно есть в G1 ИЛИ в G2
                result.matrix[i][j] = g1.matrix[i][j] || g2.matrix[i][j];
            }
        }

        return result;
    }

    // б) Пересечение графов G = G1 ∩ G2
    static GraphMatrix intersectionGraphs(const GraphMatrix& g1, const GraphMatrix& g2) {
        if (g1.vertices != g2.vertices) {
            throw invalid_argument("Графы должны иметь одинаковое количество вершин!");
        }

        int n = g1.vertices;
        GraphMatrix result(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Пересечение: ребро есть, если оно есть в G1 И в G2
                result.matrix[i][j] = g1.matrix[i][j] && g2.matrix[i][j];
            }
        }

        return result;
    }

    // в) Кольцевая сумма G = G1 ⊕ G2
    static GraphMatrix ringSumGraphs(const GraphMatrix& g1, const GraphMatrix& g2) {
        if (g1.vertices != g2.vertices) {
            throw invalid_argument("Графы должны иметь одинаковое количество вершин!");
        }

        int n = g1.vertices;
        GraphMatrix result(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Кольцевая сумма: ребро есть, если оно есть в G1 ИЛИ в G2, но не в обоих
                result.matrix[i][j] = g1.matrix[i][j] != g2.matrix[i][j];
            }
        }

        return result;
    }

    int getVerticesCount() const { return vertices; }
};

int main() {
    setlocale(LC_ALL, "rus");

    cout << "Объединение, пересечение и кольцевая сумма\n\n";

    int vertices;
    cout << "Введите количество вершин для графов: ";
    cin >> vertices;


    if (vertices <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным числом!\n";
        return 1;
    }

    // Создаем два случайных графа
    cout << "\nСоздание графов со случайными рёбрами и петлями (вероятность 50%)...\n";

    GraphMatrix g1(vertices);
    GraphMatrix g2(vertices);

    g1.print("Граф G1");
    g2.print("Граф G2");

    // Автоматически выполняем все операции
    try {
        // Объединение
        GraphMatrix unionResult = GraphMatrix::unionGraphs(g1, g2);
        unionResult.print("Объединение G1 G2");

        // Пересечение
        GraphMatrix intersectionResult = GraphMatrix::intersectionGraphs(g1, g2);
        intersectionResult.print("Пересечение G1 G2");

        // Кольцевая сумма
        GraphMatrix ringSumResult = GraphMatrix::ringSumGraphs(g1, g2);
        ringSumResult.print("Кольцевая сумма G1 G2");

    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
