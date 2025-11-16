#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "5location.h"
#include "6navigation.h"

#define INF INT_MAX
#define MAX 50   // max number of locations

// helper: index of name in names[]
static int getIndex(const char *name, char names[][30], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(names[i], name) == 0)
            return i;
    }
    return -1;
}

// build adjacency matrix from linked list map
static int buildGraphMatrix(struct Location *head, int graph[MAX][MAX], char names[][30]) {
    struct Location *temp = head;
    int count = 0;

    while (temp != NULL && count < MAX) {
        strcpy(names[count], temp->name);
        count++;
        temp = temp->next;
    }

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

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

// core dijkstra, used by both CLI + GUI
static int dijkstra_core(struct Location *head,
                         const char *start,
                         const char *end,
                         char names[][30],
                         int *outCount,
                         int parentOut[MAX],
                         int *endIndexOut,
                         int *distOut) {
    int graph[MAX][MAX];
    int count = buildGraphMatrix(head, graph, names);

    if (count == 0) return 0;

    int startIndex = getIndex(start, names, count);
    int endIndex   = getIndex(end,   names, count);

    if (startIndex == -1 || endIndex == -1)
        return 0;

    int dist[MAX], parent[MAX];
    bool visited[MAX];

    for (int i = 0; i < count; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[startIndex] = 0;

    for (int step = 0; step < count - 1; step++) {
        int min = INF, u = -1;

        for (int i = 0; i < count; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < count; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[endIndex] == INF)
        return 0;

    // copy parent + results
    for (int i = 0; i < count; i++)
        parentOut[i] = parent[i];

    *endIndexOut = endIndex;
    *distOut = dist[endIndex];
    *outCount = count;
    return 1;
}

// ============== CLI version ==============
void findShortestPath(struct Location *head, const char *start, const char *end) {
    char names[MAX][30];
    int parent[MAX], count, endIndex, totalDist;

    if (!dijkstra_core(head, start, end, names, &count, parent, &endIndex, &totalDist)) {
        printf("\nInvalid locations or no path found.\n");
        return;
    }

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

    printf("\n\nTotal Distance: %d units\n", totalDist);
    printf("====================================\n");
}

// ============== GUI helper version ==============
// fills outPath with "A -> B -> C", sets *outDistance; returns 1 on success, 0 on failure
int findShortestPathToBuffer(struct Location *head,
                             const char *start,
                             const char *end,
                             char *outPath, int outSize,
                             int *outDistance) {
    char names[MAX][30];
    int parent[MAX], count, endIndex, totalDist;

    if (!dijkstra_core(head, start, end, names, &count, parent, &endIndex, &totalDist))
        return 0;

    int path[MAX], idx = 0;
    for (int v = endIndex; v != -1; v = parent[v]) {
        path[idx++] = v;
    }

    outPath[0] = '\0';

    for (int i = idx - 1; i >= 0; i--) {
        strncat(outPath, names[path[i]], outSize - strlen(outPath) - 1);
        if (i != 0)
            strncat(outPath, " -> ", outSize - strlen(outPath) - 1);
    }

    if (outDistance)
        *outDistance = totalDist;

    return 1;
}
