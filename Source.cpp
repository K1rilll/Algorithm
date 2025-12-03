#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    int n;

    
    cout << "Введите размерность квадратной матрицы: ";
    cin >> n;

   
    if (n <= 0) {
        cout << "Размерность должна быть положительным числом!" << endl;
        return 1;
    }

    // Создание динамического двумерного массива
    int** mass = new int* [n];
    for (int i = 0; i < n; i++) {
        mass[i] = new int[n];
    }

    // Инициализация случайных чисел
    srand(time(0));

    // Заполнение массива случайными числами от -15 до 15
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                
                mass[i][j] = rand() % 31 - 15;
            }
            else {
                // Элементы выше и ниже главной диагонали
                int random_value = rand() %201 -100;
                mass[i][j] = random_value;
                mass[j][i] = random_value; 
            }
        }
    }

    // Вычисление суммы по столбцам
    int* columnSums = new int[n] {0};

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            columnSums[j] += mass[i][j];
        }
    }

    // Вывод
    cout << "\nСгенерированная симметричная матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mass[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nСуммы по столбцам:" << endl;
    for (int j = 0; j < n; j++) {
        cout << "Столбец " << j + 1 << ": " << columnSums[j] << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] mass[i];
    }
    delete[] mass;
    delete[] columnSums;
    
    return 0;
}