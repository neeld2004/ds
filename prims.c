#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100
#define INF INT_MAX
typedef struct AdjNode {
    int vertex, weight;
    struct AdjNode* next;
} AdjNode;
// Add edge to adjacency list
void addEdgeList(AdjNode* adj[], int u, int v, int w) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = adj[u];
    adj[u] = newNode;
}
// Find vertex with minimum key value from set of vertices not yet included in MST
int minKey(int key[], int mstSet[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    return min_index;
}
// Prim's algorithm using adjacency matrix
void primMatrix(int n, int graph[n][n]) {
    int parent[n]; // MST structure
    int key[n];
    int mstSet[n];
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }
    key[0] = 0;    // Start from vertex 0
    parent[0] = -1;
    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printf("Edges in MST (Prim - Matrix):\n");
    int totalWeight = 0;
    for (int i = 1; i < n; i++) {
        printf("%d - %d : %d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("Total weight of MST: %d\n", totalWeight);
}
// Prim's algorithm using adjacency list
void primList(AdjNode* adj[], int n) {
    int parent[n], key[n], mstSet[n];
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
        parent[i] = -1;
    }
    key[0] = 0;
    for (int count = 0; count < n - 1; count++) {
        // Find vertex with min key not in MST
        int u = -1, min = INF;
        for (int v = 0; v < n; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }
        mstSet[u] = 1;
        // Update key and parent of adjacent vertices
        for (AdjNode* ptr = adj[u]; ptr != NULL; ptr = ptr->next) {
            int v = ptr->vertex;
            int w = ptr->weight;
            if (!mstSet[v] && w < key[v]) {
                parent[v] = u;
                key[v] = w;
            }
        }
    }
    printf("Edges in MST (Prim - List):\n");
    int totalWeight = 0;
    for (int i = 1; i < n; i++) {
        printf("%d - %d : %d\n", parent[i], i, key[i]);
        totalWeight += key[i];
    }
    printf("Total weight of MST: %d\n", totalWeight);
}
int main() {
    int n, representation;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Choose graph representation:\n1. Adjacency Matrix\n2. Adjacency List\n");
    scanf("%d", &representation);
    switch (representation) {
        case 1: {
            int graph[n][n];
            printf("Enter adjacency matrix (0 for no edge):\n");
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    scanf("%d", &graph[i][j]);
                    if (graph[i][j] == 0) graph[i][j] = INF;
                }
            primMatrix(n, graph);
            break;
        }
        case 2: {
            AdjNode* adj[n];
            for (int i = 0; i < n; i++) adj[i] = NULL;
            printf("Enter edges (u v weight), -1 -1 -1 to stop:\n");
            while (1) {
                int u, v, w;
                scanf("%d %d %d", &u, &v, &w);
                if (u == -1 && v == -1 && w == -1) break;
                addEdgeList(adj, u, v, w);
                addEdgeList(adj, v, u, w);
            }
            primList(adj, n);
            break;
        }
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}
