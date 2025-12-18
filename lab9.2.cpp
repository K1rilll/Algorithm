#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>
#include <chrono>

using namespace std;

void DFS_List(const vector<vector<int>>& G,
    vector<int>& dist,
    int v, int d,
    vector<int>& order)
{
    dist[v] = d;
    order.push_back(v);

    for (int u : G[v]) {
        if (dist[u] == -1) {
            DFS_List(G, dist, u, d + 1, order);
        }
    }
}

void DFS_Matrix(const vector<vector<int>>& M,
    vector<int>& dist,
    int v, int d,
    vector<int>& order)
{
    dist[v] = d;
    order.push_back(v);

    int n = M.size();
    for (int u = 0; u < n; u++) {
        // Проверяем, есть ли ребро между v и u
        if (M[v][u] == 1 && dist[u] == -1) {
            DFS_Matrix(M, dist, u, d + 1, order);
        }
    }
}

void BFS_List(const vector<vector<int>>& G,
    vector<int>& dist,
    int s,
    vector<int>& order)
{
    queue<int> q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);

        for (int u : G[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    int n;
    cout << "Введите количество вершин графа: ";
    cin >> n;

    vector<vector<int>> G(n);
    vector<vector<int>> M(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int edge = rand() % 2;

            M[i][j] = M[j][i] = edge;

            if (edge == 1) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }

    cout << "\nМатрица смежности:\n    ";
    for (int j = 0; j < n; j++)
        cout << j << " ";
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << i << " | ";
        for (int j = 0; j < n; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }

    cout << "\nСписки смежности:\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int v : G[i])
            cout << v << " ";
        cout << endl;
    }

    int start;
    cout << "\nВведите начальную вершину: ";
    cin >> start;

    vector<int> distDFS_list(n, -1);
    vector<int> orderDFS_list;

    auto t1 = chrono::high_resolution_clock::now();
    DFS_List(G, distDFS_list, start, 0, orderDFS_list);
    auto t2 = chrono::high_resolution_clock::now();

    double timeDFS_list =
        chrono::duration<double, micro>(t2 - t1).count();


    vector<int> distDFS_matrix(n, -1);
    vector<int> orderDFS_matrix;

    auto t5 = chrono::high_resolution_clock::now();
    DFS_Matrix(M, distDFS_matrix, start, 0, orderDFS_matrix);
    auto t6 = chrono::high_resolution_clock::now();

    double timeDFS_matrix =
        chrono::duration<double, micro>(t6 - t5).count();

    vector<int> distBFS(n, -1);
    vector<int> orderBFS;

    auto t3 = chrono::high_resolution_clock::now();
    BFS_List(G, distBFS, start, orderBFS);
    auto t4 = chrono::high_resolution_clock::now();

    double timeBFS =
        chrono::duration<double, micro>(t4 - t3).count();

    cout << "\n==================== DFS (списки) ====================\n";
    cout << "Порядок обхода: ";
    for (int v : orderDFS_list) cout << v << " ";
    cout << "\nРасстояния:\n";
    for (int i = 0; i < n; i++) cout << i << ": " << distDFS_list[i] << endl;
    cout << "Время выполнения DFS (списки): " << timeDFS_list << " мкс\n";

    cout << "\n==================== DFS (матрица) ====================\n";
    cout << "Порядок обхода: ";
    for (int v : orderDFS_matrix) cout << v << " ";
    cout << "\nРасстояния:\n";
    for (int i = 0; i < n; i++) cout << i << ": " << distDFS_matrix[i] << endl;
    cout << "Время выполнения DFS (матрица): " << timeDFS_matrix << " мкс\n";

    cout << "\n==================== BFS (списки) ====================\n";
    cout << "Порядок обхода: ";
    for (int v : orderBFS) cout << v << " ";
    cout << "\nРасстояния:\n";
    for (int i = 0; i < n; i++) cout << i << ": " << distBFS[i] << endl;
    cout << "Время выполнения BFS: " << timeBFS << " мкс\n";

    cout << "\n=============================================\n";
    cout << "Сравнение времени:\n";
    cout << "DFS (списки): " << timeDFS_list << " мкс\n";
    cout << "DFS (матрица): " << timeDFS_matrix << " мкс\n";
    cout << "BFS (списки): " << timeBFS << " мкс\n";


    return 0;
}

