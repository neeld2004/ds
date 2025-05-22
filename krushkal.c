#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define INF 99999
// Edge structure for Kruskal
typedef struct {
    int u, v, weight;
} Edge;
// Disjoint Set Union (Union-Find) for cycle detection
int parent[MAX];
void makeSet(int n) {
    for (int i = 0; i < n; i++) parent[i] = i;
}
int findParent(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findParent(parent[x]);
}
void unionSet(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a != b) parent[b] = a;
}
// Function to sort edges by weight (for Kruskal)
int compare(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}
// Kruskal using adjacency matrix
void kruskalMatrix(int n, int graph[n][n]) {
    Edge edges[MAX * MAX];
    int edgeCount = 0;
    // Extract edges from upper triangular matrix (undirected)
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (graph[i][j] != 0 && graph[i][j] != INF) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
    qsort(edges, edgeCount, sizeof(Edge), compare);
    makeSet(n);
    printf("Edges in MST (Kruskal - Matrix):\n");
    int mstWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (findParent(u) != findParent(v)) {
            unionSet(u, v);
            printf("(%d - %d) : %d\n", u, v, edges[i].weight);
            mstWeight += edges[i].weight;
        }
    }
    printf("Total weight of MST: %d\n", mstWeight);
}
// Adjacency list node for graph edges
typedef struct AdjNode {
    int vertex, weight;
    struct AdjNode* next;
} AdjNode;
// Add edge in adjacency list
void addEdgeList(AdjNode* adj[], int u, int v, int w) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = adj[u];
    adj[u] = newNode;
}
// Convert adjacency list to edge array
int extractEdgesFromList(AdjNode* adj[], Edge edges[], int n) {
    int count = 0;
    int visited[MAX][MAX] = {0};
    for (int i = 0; i < n; i++) {
        AdjNode* curr = adj[i];
        while (curr) {
            int u = i;
            int v = curr->vertex;
            if (!visited[u][v] && !visited[v][u]) {
                edges[count].u = u;
                edges[count].v = v;
                edges[count].weight = curr->weight;
                count++;
                visited[u][v] = visited[v][u] = 1;
            }
            curr = curr->next;
        }
    }
    return count;
}
// Kruskal using adjacency list
void kruskalList(AdjNode* adj[], int n) {
    Edge edges[MAX * MAX];
    int edgeCount = extractEdgesFromList(adj, edges, n);
    qsort(edges, edgeCount, sizeof(Edge), compare);
    makeSet(n);
    printf("Edges in MST (Kruskal - List):\n");
    int mstWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (findParent(u) != findParent(v)) {
            unionSet(u, v);
            printf("(%d - %d) : %d\n", u, v, edges[i].weight);
            mstWeight += edges[i].weight;
        }
    }
    printf("Total weight of MST: %d\n", mstWeight);
}
int main() {
    int n, choice, repr;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Choose representation:\n1. Adjacency Matrix\n2. Adjacency List\n");
    scanf("%d", &repr);
    if (repr == 1) {
        int graph[n][n];
        printf("Enter adjacency matrix (use 0 for no edge):\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                scanf("%d", &graph[i][j]);
                if (graph[i][j] == 0) graph[i][j] = INF; // Mark no edge
            }
        kruskalMatrix(n, graph);
    } else if (repr == 2) {
        AdjNode* adj[n];
        for (int i = 0; i < n; i++) adj[i] = NULL;
        printf("Enter edges (u v weight). Enter -1 -1 -1 to stop:\n");
        while (1) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            if (u == -1 && v == -1 && w == -1) break;
            addEdgeList(adj, u, v, w);
            addEdgeList(adj, v, u, w); // undirected
        }
        kruskalList(adj, n);
    } else {
        printf("Invalid choice!\n");
    }
    return 0;
}
