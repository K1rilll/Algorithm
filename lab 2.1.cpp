#include <iostream>
#include <vector>
#include <random>
#include <chrono>

//#include <cstdlib>

using namespace std;
using namespace chrono;

//// Генератор случайных чисел
//random_device rd;
//mt19937 gen(rd());
//uniform_real_distribution<double> dis(0.0, 100.0);


// Функция для генерации случайной матрицы
vector<vector<double>> generateRandomMatrix(int rows, int cols) {
    vector<vector<double>> matrix(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++) {
        /*cout << "\n";*/
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0 + rand() % ((100 + 1) - 0);
            /*cout << matrix[i][j]<<" ";*/
        }
    }
    return matrix;
}

// Наивное умножение матриц (O(n³))
vector<vector<double>> naiveMatrixMultiply(const vector<vector<double>>& A,
    const vector<vector<double>>& B, int size) {
    /*int n = A.size();
    int m = A[0].size();
    int p = B[0].size();*/

    vector<vector<double>> C(size, vector<double>(size, 0.0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "");
    int SIZE;
    cout << "Размер матрицы " << endl;
    cin >> SIZE;


    cout << "Генерация матриц " << SIZE << "x" << SIZE << "..." << endl;

    // Замер времени генерации
    auto start_gen = high_resolution_clock::now();
    auto A = generateRandomMatrix(SIZE, SIZE);
    auto B = generateRandomMatrix(SIZE, SIZE);
    auto end_gen = high_resolution_clock::now();
    auto gen_time = duration_cast<milliseconds>(end_gen - start_gen).count();

    cout << "Генерация завершена за " << gen_time / 1000.0 << " секунд" << endl;
    cout << "Начинается умножение..." << endl;


    auto start_mult = high_resolution_clock::now();
    auto C = naiveMatrixMultiply(A, B, SIZE);
    auto end_mult = high_resolution_clock::now();
    auto mult_time = duration_cast<milliseconds>(end_mult - start_mult).count();


    double total_seconds = mult_time / 1000.0;

    cout << "\nРЕЗУЛЬТАТЫ:" << endl;
    cout << string(40, '=') << endl;
    cout << "Размер матриц: " << SIZE << "x" << SIZE << endl;
    cout << "Время генерации: " << gen_time / 1000.0 << " секунд" << endl;
    cout << "Время умножения: " << total_seconds << " секунд" << endl;
    cout << "Общее время: " << (gen_time + mult_time) / 1000.0 << " секунд" << endl;



    return 0;
}
