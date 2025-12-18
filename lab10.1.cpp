#include <iostream>
#include <locale.h>
#include <time.h>
#include <cstdio> 
#include <queue>
using namespace std;

void BFSD(int** G, int* dist, int numG, int** GD) {
    for (int s = 0; s < numG; s++) {
        queue<int> q;
        int v;
        //dist[s] = 0;
        q.push(s);
        GD[s][s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            printf("%3d", v);

            for (int i = 0; i < numG; i++) {

                if (G[v][i] > 0 && GD[v][i] > GD[v][v] + G[v][i]) {
                    q.push(i);
                    GD[v][i] = GD[v][v] + G[v][i];
                    dist[i] = dist[v] + 1;
                }
            }

        }
    }
    
    return;
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    int r = INT_MAX;
    int d = -1;
    int** G;
    int** GD;
    int* Ecc;
    int numG;

    std::cout << "Введите кол-во элементов: " << std::endl;
    std::cin >> numG;

    G = (int**)malloc(numG * sizeof(int*));

    GD = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
    }

    Ecc = (int*)malloc(numG * sizeof(int));

    for (int i = 0; i < numG; i++) {
        Ecc[i] = 0;
        for (int j = 0; j < numG; j++) {
            G[i][j] = G[j][i] = (i == j ? 0 : (rand() % 2 ? 0 : rand() % 11));
        }
    }

    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d ", G[i][j]);
        }
        printf("\n");
    }
    
    printf("Порядок обхода: ");
    BFSD(G, Ecc, numG, GD);

    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (Ecc[i] < GD[i][j]) {
                Ecc[i] = GD[i][j];
                
            }
 
        }
        r = ((r > Ecc[i] && Ecc[i] != 0) ? Ecc[i] : r);
        d = ((d < Ecc[i] && Ecc[i] != 0) ? Ecc[i] : d);
    }


    return 0;
}
