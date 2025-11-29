#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *front = NULL;
struct node *rear  = NULL;

void addq(struct node *head, struct node *tail, int data) {
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = NULL;

    if (front == NULL) {
        front = ptr;
        rear  = ptr;
    } else {
        rear->next = ptr;
        rear = ptr;
    }
}

int delete(struct node *head, struct node *tail) {
    char buf[100];
    if (scanf("%s", buf) != 1)
        return -1;
    return 0;
}

void print_queue(void) {
    struct node *p = front;
    while (p != NULL) {
        printf("%d \n", p->data);
        p = p->next;
    }
}

int main(void) {
    struct node *head = NULL;
    struct node *tail = NULL;
    int x;

    while (1) {
        if (scanf("%d", &x) != 1) {
            delete(head, tail);
            break;
        }

        if (x > 0) {
            addq(head, tail, x);
        } else {
            delete(head, tail);
            break;
        }
    }

    printf("Print queue\n");
    print_queue();

    return 0;
}
