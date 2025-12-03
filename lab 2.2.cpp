#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void shellSort(int arr[], int n) {

    for (int gap = n / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < n; i++) {
            int temp = arr[i];

            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << endl;
}


void fillArray(int arr[], int n) {
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
        break;
    case 2:
        for (int i = 0; i < n; i++) {
            arr[i] = n - i;
        }
        break;
    case 3:
        int j = (n - 1) / 2;
        for (int i = 0; i < j; i++) {
            arr[i] = i;
        }
        j++;
        for (int i = j - 1; i < n; i++) {
            arr[i] = j;
            j--;
        }
        break;
    }

    //for (int i = 0; i < n; i++) {
    //    arr[i] = rand() % 1000; // от 0 до 1к
    //}
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int main() {
    setlocale(LC_ALL, "");
    const int SIZE = 15206;
    int originalArray[SIZE];
    int shellArray[SIZE];
    int quickArray[SIZE];

    srand(time(NULL));

    fillArray(originalArray, SIZE);

    cout << "Исходный массив (100 элементов):" << endl;
    //printArray(originalArray, SIZE);


    copyArray(originalArray, shellArray, SIZE);

    auto start_Sort_Shell = high_resolution_clock::now();
    shellSort(shellArray, SIZE);
    auto end_Sort_Shell = high_resolution_clock::now();
    auto Sort_Shell_time = duration_cast<milliseconds>(end_Sort_Shell - start_Sort_Shell).count();
    cout << "\nМассив после сортировки Шелла:" << endl;
    //printArray(shellArray, SIZE);
    cout << "Сортировка завершена за " << Sort_Shell_time / 1000.0 << " секунд" << endl;


    copyArray(originalArray, quickArray, SIZE);

    auto start_Sort_Quick = high_resolution_clock::now();
    quickSort(quickArray, 0, SIZE - 1);
    auto end_Sort_Quick = high_resolution_clock::now();
    auto Sort_Quick_time = duration_cast<milliseconds>(end_Sort_Quick - start_Sort_Quick).count();
    cout << "\nМассив после быстрой сортировки:" << endl;
    //printArray(quickArray, SIZE);
    cout << "Сортировка завершена за " << Sort_Quick_time / 1000.0 << " секунд" << endl;


    auto start_Sort_Method = high_resolution_clock::now();
    qsort(originalArray, SIZE, sizeof(int),compare);
    auto end_Sort_Method = high_resolution_clock::now();
    auto Sort_Method_time = duration_cast<milliseconds>(end_Sort_Method - start_Sort_Method).count();
    /*cout << "\nМассив после быстрой сортировки методом :" << endl;*/
    //printArray(originalArray, SIZE);
    cout << "Сортировка завершена за " << Sort_Method_time / 1000.0 << " секунд" << endl;
    return 0;
}
