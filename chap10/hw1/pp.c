#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* push(struct node *top, int data) {
    struct node *ptr = malloc(sizeof(struct node));
    if (!ptr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ptr->data = data;
    ptr->next = top;
    return ptr;
}

struct node* pop(struct node *top) {
    if (top == NULL) {
        return NULL;
    }
    printf("%d\n", top->data);
    struct node *next = top->next;
    free(top);
    return next;
}

int main() {
    struct node *top = NULL;
    double input;

    while (scanf("%lf", &input) == 1) {
        if (input > 0 && input == (int)input) {
            top = push(top, (int)input);
        } else {
            if (input > 0) {
                top = push(top, (int)input);
            }
            break;
        }
    }

    printf("Print stack\n");
    while (top != NULL) {
        top = pop(top);
    }

    return 0;
}
