#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

// Structure for adjacency list node
struct Node {
    int data;
    struct Node* next;
};

// Queue structure for BFS
int queue[100];
int front = 0, rear = 0;

void enqueue(int x) {
    queue[rear++] = x;
}
int dequeue() {
    return queue[front++];
}
bool isQueueEmpty() {
    return front == rear;
}

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Add edge (undirected)
void addEdge(struct Node* adj[], int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = createNode(u);
    newNode->next = adj[v];
    adj[v] = newNode;
}

// Recursive BFS function
void recursiveBFS(struct Node* adj[], bool visited[]) {
    if (isQueueEmpty()) return;

    int current = dequeue();
    printf("%d ", current);

    struct Node* temp = adj[current];
    while (temp != NULL) {
        if (!visited[temp->data]) {
            visited[temp->data] = true;
            enqueue(temp->data);
        }
        temp = temp->next;
    }

    recursiveBFS(adj, visited);
}

// Display adjacency list
void displayGraph(struct Node* adj[]) {
    for (int i = 0; i < V; i++) {
        printf("%d: ", i);
        struct Node* temp = adj[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Main
int main() {
    struct Node* adj[V];
    bool visited[V];

    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
        visited[i] = false;
    }

    // Add some edges
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 4);

    printf("Adjacency List:\n");
    displayGraph(adj);

    printf("Recursive BFS starting from node 0: ");
    visited[0] = true;
    enqueue(0);
    recursiveBFS(adj, visited);

    printf("\n");
    return 0;
}
