#include <iostream>
#include <cstdlib>

typedef struct tag_obj {
    int data;
    struct tag_obj* next;
} OBJ;

typedef struct {
    OBJ* front;
    OBJ* back;
} Queue;


void initQueue(Queue* q) {
    q->front = q->back = NULL;
}


void enqueue(Queue* q, int data) {
    OBJ* ptr = (OBJ*)malloc(sizeof(OBJ));
    ptr->data = data;
    ptr->next = NULL;

    if (q->back == NULL) {

        q->front = q->back = ptr;
    }
    else {

        q->back->next = ptr;
        q->back = ptr;
    }
}

void dequeue(Queue* q) {
    if (q->front == NULL) {
        std::cout << "Очередь пуста!" << std::endl;
        return;
    }

    OBJ* temp = q->front;
    q->front = q->front->next;


    if (q->front == NULL) {
        q->back = NULL;
    }

    free(temp);
}

int front(const Queue* q) {
    if (q->front == NULL) {
        std::cout << "Очередь пуста!" << std::endl;
        return -1;
    }
    return q->front->data;
}


bool isEmpty(const Queue* q) {
    return q->front == NULL;
}


void show(const Queue* q) {
    const OBJ* current = q->front;
    std::cout << "Очередь (от начала к концу): ";
    while (current != NULL) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}


void clearQueue(Queue* q) {
    while (q->front != NULL) {
        dequeue(q);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    Queue q;
    initQueue(&q);


    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    show(&q);
    dequeue(&q);
    show(&q);


    enqueue(&q, 4);
    enqueue(&q, 5);
    show(&q);


    std::cout << "Первый элемент: " << front(&q) << std::endl;

    std::cout << "Извлекаем все элементы по порядку:" << std::endl;
    while (!isEmpty(&q)) {
        std::cout << front(&q) << " ";
        dequeue(&q);
    }
    std::cout << std::endl;

    show(&q);

    return 0;
}
