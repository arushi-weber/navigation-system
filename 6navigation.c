// 6navigation.c
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "5location.h"
#include "4search.h"
#include "6navigation.h"

#define INF INT_MAX
#define MAX 50   // max number of locations

// Helper: find index of a name in names[]
static int getIndex(const char *name, char names[][30], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(names[i], name) == 0)
            return i;
    }
    return -1;
}

// Build adjacency matrix from linked list map
static int buildGraphMatrix(struct Location *head, int graph[MAX][MAX], char names[][30]) {
    struct Location *temp = head;
    int count = 0;

    // 1) collect all node names in order
    while (temp != NULL && count < MAX) {
        strcpy(names[count], temp->name);
        count++;
        temp = temp->next;
    }

    // 2) init matrix
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    // 3) fill edges from adjacency lists
    temp = head;
    int i = 0;
    while (temp != NULL && i < count) {
        struct AdjNode *conn = temp->connections;
        while (conn != NULL) {
            int j = getIndex(conn->name, names, count);
            if (j != -1) {
                graph[i][j] = conn->distance;
            }
            conn = conn->next;
        }
        temp = temp->next;
        i++;
    }

    return count;
}

void findShortestPath(struct Location *head, const char *start, const char *end) {
    printf("\n[DEBUG] Dijkstra shortest path called for '%s' -> '%s'\n", start, end);

    int graph[MAX][MAX];
    char names[MAX][30];
    int count = buildGraphMatrix(head, graph, names);

    if (count == 0) {
        printf("Map is empty.\n");
        return;
    }

    int startIndex = getIndex(start, names, count);
    int endIndex   = getIndex(end, names, count);

    if (startIndex == -1 || endIndex == -1) {
        printf("\nInvalid locations. Please use exact names from the map.\n");
        printf("Example: RaviCanteen, HappinessHut, Gate2, BoysHostel\n");
        return;
    }

    int dist[MAX], parent[MAX];
    bool visited[MAX];

    for (int i = 0; i < count; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[startIndex] = 0;

    // Dijkstra
    for (int step = 0; step < count - 1; step++) {
        int min = INF, u = -1;

        for (int i = 0; i < count; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break;   // unreachable nodes

        visited[u] = true;

        for (int v = 0; v < count; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[endIndex] == INF) {
        printf("\nNo path found between %s and %s.\n", start, end);
        return;
    }

    // reconstruct path
    int path[MAX], idx = 0;
    for (int v = endIndex; v != -1; v = parent[v]) {
        path[idx++] = v;
    }

    printf("\n======= SHORTEST PATH RESULT =======\n");
    printf("Start: %s\nDestination: %s\n\nPath:\n", start, end);

    for (int i = idx - 1; i >= 0; i--) {
        printf("%s", names[path[i]]);
        if (i != 0) printf(" -> ");
    }

    printf("\n\nTotal Distance: %d units\n", dist[endIndex]);
    printf("====================================\n");
}
