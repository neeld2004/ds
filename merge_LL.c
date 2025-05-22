#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Split the list into halves
void splitList(struct Node* source, struct Node** front, struct Node** back) {
    struct Node *slow = source, *fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

// Merge two sorted lists
struct Node* merge(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;

    struct Node* result;
    if (a->data <= b->data) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }
    return result;
}

// Merge Sort
void mergeSort(struct Node** headRef) {
    struct Node* head = *headRef;
    if (!head || !head->next) return;

    struct Node *a, *b;
    splitList(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = merge(a, b);
}

// Utility to insert at head
void push(struct Node** headRef, int data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *headRef;
    *headRef = newNode;
}

// Utility to print list
void printList(struct Node* node) {
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;

    push(&head, 15);
    push(&head, 10);
    push(&head, 5);
    push(&head, 20);
    push(&head, 3);
    push(&head, 2);

    printf("Unsorted list: ");
    printList(head);

    mergeSort(&head);

    printf("\nSorted list: ");
    printList(head);
    return 0;
}
