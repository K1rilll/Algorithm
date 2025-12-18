#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <locale.h>

using namespace std;

void BFS_List(const vector<vector<int>>& G, vector<int>& dist, int s) {
    
    queue<int> q;
    dist[s] = 0;
    q.push(s);
 

    cout << "\nПорядок обхода (BFS): ";

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";

        for (int u : G[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
   
    cout << "\n\nРасстояния от вершины " << s << ":\n";
    for (int i = 0; i < dist.size(); i++) {
        cout << i << ": " << dist[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    int numG;
    cout << "Введите количество вершин: ";
    cin >> numG;

    vector<vector<int>> G(numG);        // списки смежности
    vector<vector<int>> M(numG, vector<int>(numG, 0)); // матрица смежности
    vector<int> dist(numG, -1);

    // Генерация случайного неориентированного графа
    for (int i = 0; i < numG; i++) {
        for (int j = i + 1; j < numG; j++) {
            int edge = rand() %2;  // 0 или 1
            M[i][j] = M[j][i] = edge;

            if (edge == 1) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }

    // ❗️ Вывод матрицы смежности
    cout << "\nМатрица смежности:\n";
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }

    // ❗️ Вывод списков смежности
    cout << "\nСписки смежности:\n";
    for (int i = 0; i < numG; i++) {
        cout << i << ": ";
        for (int v : G[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    int s;
    cout << "\nВведите начальную вершину: ";
    cin >> s;
    
    if (G[s].empty()) {
        cout << "изол" << endl;
        return 0;
    }
    BFS_List(G, dist, s);
    

    return 0;
}
