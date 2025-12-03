#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

double getTimeSeconds() {
    return duration_cast<duration<double>>(
        high_resolution_clock::now().time_since_epoch()
    ).count();
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void shellSort(int* arr, int n) {
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

int partition(int* arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];
    swap(arr[mid], arr[high]);

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int* arr, int low, int high) {
    while (low < high) {
        int pi = partition(arr, low, high);

        if (pi - low < high - pi) {
            quickSort(arr, low, pi - 1);
            low = pi + 1;
        }
        else {
            quickSort(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

void printArray(const int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << endl;
}

int* createAndFillArray(int n, int choice) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == nullptr) {
        cerr << "Îøèáêà âûäåëåíèÿ ïàìÿòè!" << endl;
        return nullptr;
    }

    switch (choice) {
    case 1:
        for (int i = 0; i < n; i++) arr[i] = i;
        break;
    case 2:
        for (int i = 0; i < n; i++) arr[i] = n - i;
        break;
    case 3:
    {
        int j = (n - 1) / 2;
        for (int i = 0; i < j; i++) arr[i] = i;
        for (int i = j; i < n; i++) arr[i] = n - i;
    }
    break;
    case 4:
        for (int i = 0; i < n; i++) arr[i] = rand() % 1000;
        break;
    }

    return arr;
}

void copyArray(const int* source, int* dest, int n) {
    for (int i = 0; i < n; i++) dest[i] = source[i];
}

double testSort(void (*sortFunc)(int*, int), const int* arr, int n) {
    int* testArr = (int*)malloc(n * sizeof(int));
    if (testArr == nullptr) {
        cerr << "Îøèáêà âûäåëåíèÿ ïàìÿòè!" << endl;
        return 0;
    }
    copyArray(arr, testArr, n);

    double start = getTimeSeconds();
    sortFunc(testArr, n);
    double end = getTimeSeconds();

    free(testArr);
    return end - start;
}

double testQuickSort(const int* arr, int n) {
    int* testArr = (int*)malloc(n * sizeof(int));
    if (testArr == nullptr) {
        cerr << "Îøèáêà âûäåëåíèÿ ïàìÿòè!" << endl;
        return 0;
    }
    copyArray(arr, testArr, n);

    double start = getTimeSeconds();
    quickSort(testArr, 0, n - 1);
    double end = getTimeSeconds();

    free(testArr);
    return end - start;
}


double testQsort(const int* arr, int n) {
    int* testArr = (int*)malloc(n * sizeof(int));
    if (testArr == nullptr) {
        cerr << "Îøèáêà âûäåëåíèÿ ïàìÿòè!" << endl;
        return 0;
    }
    copyArray(arr, testArr, n);

    double start = getTimeSeconds();
    qsort(testArr, n, sizeof(int), compare);
    double end = getTimeSeconds();

    free(testArr);
    return end - start;
}

void printTableHeader() {
    cout << setw(20) << "Òèï ìàññèâà"
        << setw(20) << "Shell Sort (ñåê)"
        << setw(20) << "Quick Sort (ñåê)"
        << setw(20) << "qsort() (ñåê)"
        << endl;
    cout << string(80, '-') << endl;
}


void printTableRow(const string& arrayType, double shellTime,
    double quickTime, double qsortTime) {
    cout << setw(20) << arrayType
        << setw(20) << fixed << setprecision(6) << shellTime
        << setw(20) << fixed << setprecision(6) << quickTime
        << setw(20) << fixed << setprecision(6) << qsortTime
        << endl;
}

void runTests(int size) {
    cout << "\nÐÅÇÓËÜÒÀÒÛ ÄËß ÐÀÇÌÅÐÀ ÌÀÑÑÈÂÀ: " << size << endl;

    string arrayTypes[] = { "Óïîðÿäî÷åííûé", "Îáðàòíûé", "×àñòè÷íûé", "Ñëó÷àéíûé" };

    printTableHeader();

    for (int i = 1; i <= 4; i++) {
        int* originalArray = createAndFillArray(size, i);
        if (originalArray == nullptr) {
            cerr << "Îøèáêà âûäåëåíèÿ ïàìÿòè äëÿ ìàññèâà ðàçìåðà " << size << endl;
            continue;
        }

        double shellTime = testSort(shellSort, originalArray, size);
        double quickTime = testQuickSort(originalArray, size);
        double qsortTime = testQsort(originalArray, size);

        printTableRow(arrayTypes[i - 1], shellTime, quickTime, qsortTime);

        free(originalArray);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    cout << "ÑÐÀÂÍÅÍÈÅ ÀËÃÎÐÈÒÌÎÂ ÑÎÐÒÈÐÎÂÊÈ" << endl;
    cout << "================================" << endl;

    runTests(100);
    runTests(10000);

    return 0;
}
