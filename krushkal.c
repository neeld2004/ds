#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Edge structure
struct Edge {
    int src, dest, weight;
};

// Adjacency List Node
struct Node {
    int dest, weight;
    struct Node* next;
};

// Disjoint Set (Union-Find)
int parent[MAX];

int find(int i) {
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

void unionSet(int u, int v) {
    int uRoot = find(u);
    int vRoot = find(v);
    parent[uRoot] = vRoot;
}

// Compare function for qsort
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// ---------------- Matrix Implementation ----------------
void kruskalMatrix(int graph[MAX][MAX], int V) {
    struct Edge edges[MAX * MAX];
    int edgeCount = 0;

    // Convert matrix to edge list
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j]) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges by weight
    qsort(edges, edgeCount, sizeof(struct Edge), compareEdges);

    for (int i = 0; i < V; i++) parent[i] = i;

    printf("\nMST using Adjacency Matrix:\n");
    int mstCost = 0, count = 0;
    for (int i = 0; i < edgeCount && count < V - 1; i++) {
        int u = edges[i].src, v = edges[i].dest;
        if (find(u) != find(v)) {
            unionSet(u, v);
            printf("Edge (%d - %d) Cost: %d\n", u, v, edges[i].weight);
            mstCost += edges[i].weight;
            count++;
        }
    }

    printf("Total Cost: %d\n", mstCost);
}

// ---------------- List Implementation ----------------
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

    node = createNode(u, w); // Since undirected
    node->next = adj[v];
    adj[v] = node;
}

void kruskalList(struct Node* adj[], int V) {
    struct Edge edges[MAX * MAX];
    int edgeCount = 0;

    int added[MAX][MAX] = {0}; // to avoid duplicate undirected edges

    // Convert list to edge list
    for (int u = 0; u < V; u++) {
        struct Node* temp = adj[u];
        while (temp) {
            int v = temp->dest;
            if (!added[u][v] && !added[v][u]) {
                edges[edgeCount++] = (struct Edge){u, v, temp->weight};
                added[u][v] = added[v][u] = 1;
            }
            temp = temp->next;
        }
    }

    qsort(edges, edgeCount, sizeof(struct Edge), compareEdges);

    for (int i = 0; i < V; i++) parent[i] = i;

    printf("\nMST using Adjacency List:\n");
    int mstCost = 0, count = 0;
    for (int i = 0; i < edgeCount && count < V - 1; i++) {
        int u = edges[i].src, v = edges[i].dest;
        if (find(u) != find(v)) {
            unionSet(u, v);
            printf("Edge (%d - %d) Cost: %d\n", u, v, edges[i].weight);
            mstCost += edges[i].weight;
            count++;
        }
    }

    printf("Total Cost: %d\n", mstCost);
}

// ---------------- Main ----------------
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
        kruskalMatrix(graph, V);
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
        kruskalList(adj, V);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
