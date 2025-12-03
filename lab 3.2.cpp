#include <iostream>
#include <cstdlib>

typedef struct tag_obj {
    int data;
    struct tag_obj* next;
} OBJ;

OBJ* push(OBJ* top, int data) {
    OBJ* ptr = (OBJ*)malloc(sizeof(OBJ));
    ptr->data = data;
    ptr->next = top;
    return ptr;
}

OBJ* pop(OBJ* top) {
    if (top == NULL)
        return top;
    OBJ* ptr_next = top->next;
    free(top);
    return ptr_next;
}

void show(const OBJ* top) {
    const OBJ* current = top;
    while (current != NULL) {
        std::cout << current->data << std::endl;
        current = current->next;
    }
}

int main()
{
    OBJ* top = NULL;
    top = push(top, 1);
    top = push(top, 2);
    top = push(top, 3);
    show(top);
    top = pop(top);
    show(top);
    return 0;
}
