#include <iostream>
#include <locale.h>
#include <time.h>
#include <cstdio> 
#include <queue>
#include <vector>
#include <list>
using namespace std;



bool is_vert(vector<list<int>>& adjlist, int vertex) {
    return adjlist[vertex].begin() == adjlist[vertex].end();
}
// Обход в ширину для матрицы смежности
void BFS_matrix(int** G, int* vis, int numG, int s) {
    queue<int> q;
    vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        printf("%3d", v);
        for (int i = 0; i < numG; i++) {
            if (vis[i] == 0 && G[v][i] == 1) {
                q.push(i);
                vis[i] = 1;
            }
        }
    }
}

// Обход в ширину для списков смежности
void BFS_adjacency_list(vector<list<int>>& adjList, int* vis, int numG, int s) {
    queue<int> q;
    vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        printf("%3d", v);
        // Проходим по всем соседям вершины v
        for (auto it = adjList[v].begin(); it != adjList[v].end(); ++it) {
            int neighbor = *it;
            if (vis[neighbor] == 0) {
                q.push(neighbor);
                vis[neighbor] = 1;
            }
        }
    }
}

// Функция для создания списков смежности из матрицы смежности
vector<list<int>> create_adjacency_list(int** G, int numG) {
    vector<list<int>> adjList(numG);
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (G[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

// Функция для вывода списков смежности
void print_adjacency_list(vector<list<int>>& adjList, int numG) {
    cout << "Списки смежности:" << endl;
    
    for (int i = 0; i < numG; i++) {
        cout << i << ": ";
        auto it = adjList[i].begin();
         
            if (it == adjList[i].end()) {
                cout << "isol" << " ";
            }else{ cout << *it << " "; }
           
            
        
        cout << endl;
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");

    int** G;
    int* vis;
    int numG, s;

    cout << "Введите количество вершин графа: ";
    cin >> numG;

    // Выделение памяти для матрицы смежности
    G = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
    }

    // Выделение памяти для массива посещенных вершин
    vis = (int*)malloc(numG * sizeof(int));

   
    for (int i = 0; i < numG; i++) {
        for (int j = i; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                G[i][j] = G[j][i] = rand()%2; // Симметричная матрица
            }
        }
    }

  
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d ", G[i][j]);
        }
        printf("\n");
    }


    cout << "Введите начальную вершину для обхода в ширину: ";
    cin >> s;

    // Инициализация массива посещенных вершин
    for (int i = 0; i < numG; i++) {
        vis[i] = 0;
    }
    
        cout << "Порядок обхода (матрица смежности): ";
        BFS_matrix(G, vis, numG, s);
        cout << endl;
    
    
   
    vector<list<int>> adjList = create_adjacency_list(G, numG);
    if (is_vert) {
        cout << "выбрана не правильная вершина для обхода";
        return 0;
    }
    print_adjacency_list(adjList, numG);

    for (int i = 0; i < numG; i++) {
        vis[i] = 0;
    }
    
        cout << "Порядок обхода (списки смежности): ";
        BFS_adjacency_list(adjList, vis, numG, s);
        cout << endl;
    
    

    // Освобождение памяти
    for (int i = 0; i < numG; i++) {
        free(G[i]);
    }
    free(G);
    free(vis);

    return 0;
}
