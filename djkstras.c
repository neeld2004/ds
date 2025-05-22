#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

// Structure for adjacency list node
struct Node {
    int dest, weight;
    struct Node* next;
};

// Create a new list node
struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Add edge to adjacency list
void addEdgeList(struct Node* adj[], int u, int v, int w) {
    struct Node* node = createNode(v, w);
    node->next = adj[u];
    adj[u] = node;

    node = createNode(u, w);
    node->next = adj[v];
    adj[v] = node;
}

// Find vertex with minimum key value
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra using adjacency matrix
void dijkstraMatrix(int graph[MAX][MAX], int V, int src) {
    int dist[MAX];
    bool visited[MAX];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

// Dijkstra using adjacency list
void dijkstraList(struct Node* adj[], int V, int src) {
    int dist[MAX];
    bool visited[MAX];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = true;

        struct Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->dest;
            int weight = temp->weight;

            if (!visited[v] && dist[u] != INT_MAX &&
                dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }

            temp = temp->next;
        }
    }

    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

int main() {
    int choice, V, E;
    int graph[MAX][MAX] = {0};
    struct Node* adj[MAX];
    for (int i = 0; i < MAX; i++) adj[i] = NULL;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Choose graph representation:\n1. Adjacency Matrix\n2. Adjacency List\nEnter choice: ");
    scanf("%d", &choice);

    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter edges (src dest weight):\n");

    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--; // convert to 0-based index

        if (choice == 1) {
            graph[u][v] = w;
            graph[v][u] = w;
        } else {
            addEdgeList(adj, u, v, w);
        }
    }

    int src;
    printf("Enter source vertex (1 to %d): ", V);
    scanf("%d", &src);
    src--; // Convert to 0-based

    if (choice == 1) {
        printf("\nDijkstra using Adjacency Matrix:\n");
        dijkstraMatrix(graph, V, src);
    } else {
        printf("\nDijkstra using Adjacency List:\n");
        dijkstraList(adj, V, src);
    }

    return 0;
}
