#include <iostream>
using namespace std;
class BST {
    struct Node
    {
        int key;
        Node* l = nullptr;
        Node* r = nullptr;
        Node(int key) : key(key) {};

    }*root = nullptr;

    int contains(Node* n, int key, int count) const {
        if (!n) {
            //cout << key << " не было обнаруженно" << endl;
            return 0;
        }
        if (key == n->key) {
            cout << "найденно число " << key << "его глубина "<<count<< endl;
            //return count;
        }

        if (key < n->key)
            return contains(n->l, key, count+1);
        else
            return contains(n->r, key, count+1);

    }

    void num_of_app(Node* n, int key, int& count) const {
        if (!n) return;

 
        num_of_app(n->l, key, count);
        if (n->key == key)
            count++;
        num_of_app(n->r, key, count);

    }

    void insert(Node*& n, int key) {
        if (!n) {
            n = new Node(key);
            return;
        }
        /* if (key == n->key)
             return;*/
        if (key < n->key)
            insert(n->l, key);
        else
            insert(n->r, key);

    }

    /*void print(Node* n) const {
        if (!n)
            return;
        print(n->l);
        cout << n->key << "\n";
        print(n->r);
    }*/


    void print(const string& prefix, const Node* node, bool isLeft) const {
        if (node != nullptr) {
            cout << prefix;
            cout << (isLeft ? "|__" : "|--");
            cout << node->key << endl;

            print(prefix + (isLeft ? "|   " : "    "), node->l, true);
            print(prefix + (isLeft ? "|   " : "    "), node->r, false);
        }
    }
    void print(const Node* node) const {
        print("", node, false);
    }
public:
    void printTree() const {
        cout << "Структура дерева:\n";
        print(root);
    }
    bool contains(int key) const {
        int count = 0;
        return contains(root, key, count);
    }

    void insert(int key) {
        insert(root, key);
    }

    void print() const {
        print(root);
    }

    void num_of_app(int key, int& count) const {
        count = 0;
        return num_of_app(root, key, count);
    }
};
int main()
{
    setlocale(LC_ALL, "");
    BST bst;
    int choice, x, count,depth;

    while (true) {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Заполнить дерево числами\n";
        cout << "2. Найти элемент\n";
        cout << "3. Подсчитать число вхождений элемента\n";
        cout << "4. Показать дерево\n";
        cout << "5. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите числа для вставки (0 — конец ввода):\n";
            while (true) {
                cin >> x;
                if (x == 0)
                    break;
                bst.insert(x);
            }
            cout << "Дерево заполнено.\n";
            break;

        case 2:
            cout << "Введите число для поиска: ";
            cin >> x;
            depth = bst.contains(x);
                //cout << "Число " << x << " найдено в дереве. "<< depth<<"раз";
            
            break;

        case 3:
            cout << "Введите число для подсчёта вхождений: ";
            cin >> x;
            count = 0;
            bst.num_of_app(x, count);
            cout << "Число " << x << " встречается в дереве " << count << " раз(а).\n";
            break;

        case 4:
            bst.print();
            break;

        case 5:
            cout << "Выход из программы.\n";
            return 0;

        default:
            cout << "Неверный пункт меню, попробуйте снова.\n";
            break;
        }
    }
}
