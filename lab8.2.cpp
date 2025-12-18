#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <memory>

// Узел для собственной реализации списка
template<typename T>
class ListNode {
public:
    T data;
    std::shared_ptr<ListNode<T>> next;

    ListNode(const T& value) : data(value), next(nullptr) {}
};

// Самостоятельная реализация очереди на основе списка
template<typename T>
class CustomQueue {
private:
    std::shared_ptr<ListNode<T>> front;
    std::shared_ptr<ListNode<T>> rear;
    size_t queueSize;

public:
    CustomQueue() : front(nullptr), rear(nullptr), queueSize(0) {}

    // Добавление элемента в очередь
    void push(const T& value) {
        auto newNode = std::make_shared<ListNode<T>>(value);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        queueSize++;
    }

    // Удаление элемента из очереди
    void pop() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        queueSize--;
    }

    // Получение первого элемента
    T& getFront() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }

    // Проверка на пустоту
    bool empty() const {
        return front == nullptr;
    }

    // Получение размера очереди
    size_t size() const {
        return queueSize;
    }
};

// Класс для представления графа в матричной форме
class Graph {
private:
    std::vector<std::vector<int>> adjacencyMatrix;
    int vertices;

public:
    Graph(int n) : vertices(n) {
        adjacencyMatrix.resize(n, std::vector<int>(n, 0));
    }

    // Добавление ребра
    void addEdge(int u, int v) {
        if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
            adjacencyMatrix[u][v] = 1;
            adjacencyMatrix[v][u] = 1; // Для неориентированного графа
        }
    }

    // Генерация случайного графа
    void generateRandomGraph(double density = 0.3) {
        srand(time(nullptr));
        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (static_cast<double>(rand()) / RAND_MAX < density) {
                    addEdge(i, j);
                }
            }
        }
    }

    // BFS с использованием стандартной очереди
    std::vector<int> bfsWithStdQueue(int startVertex) {
        std::vector<int> traversalOrder;
        std::vector<bool> visited(vertices, false);
        std::queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            traversalOrder.push_back(current);

            for (int i = 0; i < vertices; i++) {
                if (adjacencyMatrix[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        return traversalOrder;
    }

    // BFS с использованием собственной очереди
    std::vector<int> bfsWithCustomQueue(int startVertex) {
        std::vector<int> traversalOrder;
        std::vector<bool> visited(vertices, false);
        CustomQueue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.getFront();
            q.pop();
            traversalOrder.push_back(current);

            for (int i = 0; i < vertices; i++) {
                if (adjacencyMatrix[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        return traversalOrder;
    }

    // Вывод матрицы смежности (для отладки)
    void printAdjacencyMatrix() {
        std::cout << "Матрица смежности:\n";
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    int getVerticesCount() const {
        return vertices;
    }
};

// Функция для измерения времени выполнения
template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    setlocale(LC_ALL, "rus");
    std::vector<int> graphSizes = { 10, 50, 100, 200, 500, 1000 };
    int startVertex = 0;

    std::cout << "Сравнение времени выполнения BFS с разными реализациями очереди:\n";

    for (int size : graphSizes) {
        std::cout << "\nГраф порядка " << size << ":\n";

        Graph graph(size);
        graph.generateRandomGraph(0.1); // Плотность 10%

        // Измерение времени для стандартной очереди
        double stdQueueTime = measureTime([&]() {
            auto result = graph.bfsWithStdQueue(startVertex);
            });

        // Измерение времени для собственной очереди
        double customQueueTime = measureTime([&]() {
            auto result = graph.bfsWithCustomQueue(startVertex);
            });

        std::cout << "Стандартная очередь: " << stdQueueTime << " секунд\n";
        std::cout << "Собственная очередь: " << customQueueTime << " секунд\n";
        std::cout << "Отношение (собственная/стандартная): " << customQueueTime / stdQueueTime << "\n";

        // Проверка корректности (должны давать одинаковый результат)
        auto result1 = graph.bfsWithStdQueue(startVertex);
        auto result2 = graph.bfsWithCustomQueue(startVertex);

        if (result1 == result2) {
            std::cout << "Результаты совпадают\n";
        }
        else {
            std::cout << "Результаты не совпадают!\n";
        }
    }

    // Демонстрация работы на маленьком графе
    std::cout << "\n\nДемонстрация на маленьком графе:\n";
    std::cout << "==================================\n";

    Graph demoGraph(6);
    demoGraph.addEdge(0, 1);
    demoGraph.addEdge(0, 2);
    demoGraph.addEdge(1, 3);
    demoGraph.addEdge(1, 4);
    demoGraph.addEdge(2, 5);

    demoGraph.printAdjacencyMatrix();

    auto resultStd = demoGraph.bfsWithStdQueue(0);
    auto resultCustom = demoGraph.bfsWithCustomQueue(0);

    std::cout << "\nBFS с стандартной очередью: ";
    for (int vertex : resultStd) {
        std::cout << vertex << " ";
    }
    std::cout << "\n";

    std::cout << "BFS с собственной очередью: ";
    for (int vertex : resultCustom) {
        std::cout << vertex << " ";
    }
    std::cout << "\n";

    return 0;
}
