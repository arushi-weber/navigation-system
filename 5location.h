#ifndef LOCATION_H
#define LOCATION_H

struct AdjNode {
    char name[30];
    int distance;
    struct AdjNode *next;
};

struct Location {
    char name[30];
    struct AdjNode *connections;
    struct Location *next;
};

struct Location* buildMap();
void printMap(struct Location *head);

#endif