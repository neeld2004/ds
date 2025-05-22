#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Add an undirected edge to the graph
void addEdge(struct Node* adj[], int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = createNode(u);  // Because it's undirected
    newNode->next = adj[v];
    adj[v] = newNode;
}

// DFS function (recursive)
void DFS(struct Node* adj[], int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);

    struct Node* temp = adj[v];
    while (temp != NULL) {
        int neighbor = temp->data;
        if (!visited[neighbor]) {
            DFS(adj, neighbor, visited);
        }
        temp = temp->next;
    }
}

// Display the graph
void displayGraph(struct Node* adj[], int V) {
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

// Main function
int main() {
    int V = 5;
    struct Node* adj[V];
    bool visited[V];

    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
        visited[i] = false;
    }

    // Add edges
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 4);

    printf("Adjacency List:\n");
    displayGraph(adj, V);

    printf("DFS traversal starting from vertex 0: ");
    DFS(adj, 0, visited);

    printf("\n");
    return 0;
}
