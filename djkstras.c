#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100
#define INF INT_MAX
typedef struct AdjNode {
    int vertex, weight;
    struct AdjNode* next;
} AdjNode;
void addEdgeList(AdjNode* adj[], int u, int v, int w) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = adj[u];
    adj[u] = newNode;
}
int minDistance(int dist[], int sptSet[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}
// Dijkstra with adjacency matrix
void dijkstraMatrix(int n, int graph[n][n], int src) {
    int dist[n], sptSet[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }
    dist[src] = 0;
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}
// Dijkstra with adjacency list
void dijkstraList(AdjNode* adj[], int n, int src) {
    int dist[n], sptSet[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }
    dist[src] = 0;
    for (int count = 0; count < n - 1; count++) {
        int u = -1, min = INF;
        for (int i = 0; i < n; i++)
            if (!sptSet[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        if (u == -1) break;
        sptSet[u] = 1;
        for (AdjNode* curr = adj[u]; curr != NULL; curr = curr->next) {
            int v = curr->vertex;
            int w = curr->weight;
            if (!sptSet[v] && dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}
int main() {
    int n, representation, source;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Choose graph representation:\n1. Adjacency Matrix\n2. Adjacency List\n");
    scanf("%d", &representation);
    printf("Enter source vertex: ");
    scanf("%d", &source);
    switch (representation) {
        case 1: {
            int graph[n][n];
            printf("Enter adjacency matrix (0 for no edge):\n");
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    scanf("%d", &graph[i][j]);
                    if (graph[i][j] == 0) graph[i][j] = INF;
                }
            dijkstraMatrix(n, graph, source);
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
                // For undirected graph, also add opposite edge:
                addEdgeList(adj, v, u, w);
            }
            dijkstraList(adj, n, source);
            break;
        }
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}
