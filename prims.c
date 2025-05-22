#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

// ----------- Matrix Representation ------------
void primMatrix(int graph[MAX][MAX], int V) {
    int key[V], parent[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX, u;

        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nMST using Adjacency Matrix:\n");
    int totalCost = 0;
    for (int i = 1; i < V; i++) {
        printf("Edge (%d - %d) Weight: %d\n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }
    printf("Total Cost: %d\n", totalCost);
}

// ---------- List Representation ----------------
struct Node {
    int dest, weight;
    struct Node* next;
};

struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Node* adj[], int u, int v, int w) {
    struct Node* node = createNode(v, w);
    node->next = adj[u];
    adj[u] = node;

    node = createNode(u, w); // undirected
    node->next = adj[v];
    adj[v] = node;
}

void primList(struct Node* adj[], int V) {
    int key[V], parent[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX, u = -1;
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        struct Node* temp = adj[u];
        while (temp) {
            int v = temp->dest;
            if (!mstSet[v] && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printf("\nMST using Adjacency List:\n");
    int totalCost = 0;
    for (int i = 1; i < V; i++) {
        printf("Edge (%d - %d) Weight: %d\n", parent[i], i, key[i]);
        totalCost += key[i];
    }
    printf("Total Cost: %d\n", totalCost);
}

// ---------------- Main Function ------------------
int main() {
    int V, E, choice;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Choose graph representation:\n1. Adjacency Matrix\n2. Adjacency List\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int graph[MAX][MAX] = {0};
        printf("Enter number of edges: ");
        scanf("%d", &E);
        printf("Enter edges (src dest weight):\n");
        for (int i = 0; i < E; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            graph[u][v] = w;
            graph[v][u] = w;
        }
        primMatrix(graph, V);
    } else if (choice == 2) {
        struct Node* adj[MAX] = {NULL};
        printf("Enter number of edges: ");
        scanf("%d", &E);
        printf("Enter edges (src dest weight):\n");
        for (int i = 0; i < E; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            addEdge(adj, u, v, w);
        }
        primList(adj, V);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
