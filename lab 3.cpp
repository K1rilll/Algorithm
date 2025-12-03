#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
using namespace std;

struct Task {
    string name;
    int priority; // 1 - наивысший, 3 - наименьший
};

class PriorityQueue {
private:
    vector<Task> heap;

    // Для min-heap (приоритет 1 важнее 3)
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) ;
            if (heap[index].priority >= heap[parent].priority)
                break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = index + 1;
            int right =index + 2;
            int smallest = index;

            if (left < size && heap[left].priority < heap[smallest].priority)
                smallest = left;
            if (right < size && heap[right].priority < heap[smallest].priority)
                smallest = right;

            if (smallest == index)
                break;

            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    void push(const Task& task) {
        // Проверка корректности приоритета
       
        heap.push_back(task);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty())
            throw runtime_error("Очередь пуста");
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            heapifyDown(0);
    }

    Task top() const {
        if (heap.empty())
            throw runtime_error("Очередь пуста");
        return heap[0];
    }

    bool empty() const { return heap.empty(); }

    int size() const { return heap.size(); }

    // Функция для удаления задачи по определенному приоритету
    bool removeByPriority(int priority) {
        

        for (size_t i = 0; i < heap.size(); i++) {
            if (heap[i].priority == priority) {
              
                heap[i] = heap.back();
                heap.pop_back();

             
                if (i < heap.size()) {
                    heapifyUp(i);
                    heapifyDown(i);
                }
                return true;
            }
        }
        cout << "Задача с приоритетом " << priority << " не найдена.\n";
        return false;
    }

    void printAll() const {
        if (heap.empty()) {
            cout << "Очередь пуста.\n";
            return;
        }

        cout << left << setw(25) << "Название задачи" << "Приоритет\n";
        cout << string(40, '-') << "\n";
        for (const auto& t : heap)
            cout << left << setw(25) << t.name << t.priority << "\n";
    }

};

int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 1251 > nul");
    PriorityQueue pq;
    int choice;

    do {
        cout << "\n=== Меню приоритетной очереди ===\n";
        cout << "1. Добавить задачу\n";
        cout << "2. Показать самую важную задачу\n";
        cout << "3. Удалить выполненную задачу (с наивысшим приоритетом)\n";
        cout << "4. Показать все задачи\n";
        cout << "5. Удалить задачу по определенному приоритету\n";
       
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            Task t;

            
            cout << "Введите название задачи: ";
            getline(cin, t.name);
            cout << "Введите приоритет 1 - наивысший ";
            cin >> t.priority;


            pq.push(t);
            cout << "Задача добавлена!\n";
            break;
        }
        case 2:
            if (!pq.empty()) {
                Task top = pq.top();
                cout << "\nСамая важная задача:\n";
                cout << "Название: " << top.name << "\nПриоритет: " << top.priority << "\n";
            }
            else {
                cout << "Очередь пуста.\n";
            }
            break;
        case 3:
            if (!pq.empty()) {
                Task t = pq.top();
                pq.pop();
                cout << "Задача \"" << t.name << "\" с приоритетом " << t.priority << " выполнена и удалена.\n";
            }
            else {
                cout << "Очередь пуста.\n";
            }
            break;
        case 4:
            setlocale(LC_ALL, "ru");
            pq.printAll();
            break;
        case 5: {
            if (pq.empty()) {
                cout << "Очередь пуста.\n";
                cout << "Очередь пуста.\n";
                break;
            }
            int priority;
            cout << "Введите приоритет для удаления : ";
            cin >> priority;
          
            if (pq.removeByPriority(priority)) {
                cout << "Задача с приоритетом " << priority << " удалена.\n";
            }
            break;
        }
        
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор. Повторите ввод.\n";
        }

    } while (choice != 0);

    return 0;
}