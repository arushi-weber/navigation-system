#ifndef LOCATION_H
#define LOCATION_H

struct AdjNode {
    char name[50];
    int distance;
    struct AdjNode *next;
};

struct Location {
    char name[50];
    struct AdjNode *connections;
    struct Location *next;
};

// Declare all functions implemented in location.c
struct Location* buildMap();
void printMap(struct Location *head);
void findShortestPath(struct Location *head, const char *start, const char *dest);

#endif
