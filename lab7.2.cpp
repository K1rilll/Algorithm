#include <iostream>
#include <locale.h>
#include <time.h>
#include <stack>

void DFS(int** G1, int* vis, int s, int num) {
    std::stack<int> stack;
    stack.push(s);
    vis[s] = 1;

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        std::cout << " " << current << " ";

        // Обрабатываем соседей в обратном порядке для сохранения порядка обхода
        for (int i = num - 1; i >= 0; i--) {
            if (G1[current][i] == 1 && vis[i] == 0) {
                vis[i] = 1;
                stack.push(i);
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    int** G1;
    int* vis;
    int s, num;

    std::cout << "Введите кол элм" << std::endl;
    std::cin >> num;

    G1 = (int**)malloc(num * sizeof(int*));
    vis = (int*)malloc(num * sizeof(int));

    for (int i = 0; i < num; i++) {
        G1[i] = (int*)malloc(num * sizeof(int));
    }
    for (int i = 0; i < num; i++) {
        vis[i] = 0;
        for (int j = i; j < num; j++) {
            if (i == j) {
                G1[i][j] = 0;
            }
            else {
                G1[i][j] = G1[j][i] = rand() % 2;
            }
        }
    }

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            std::cout << " " << G1[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "начальная вершина обхода: " << std::endl;
    std::cin >> s;
    std::cout << "Порядок обхода " << std::endl;
    DFS(G1, vis, s, num);

    // Освобождение памяти
    for (int i = 0; i < num; i++) {
        free(G1[i]);
    }
    free(G1);
    free(vis);

    return 0;
}
