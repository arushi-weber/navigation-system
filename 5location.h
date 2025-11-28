#ifndef LOCATION_H
#define LOCATION_H

struct AdjNode {
    char name[30];            // connected place
    int distance;             // distance in meters
    struct AdjNode *next;     // next connection
};

struct Location {
    char name[30];            // location name
    struct AdjNode *connections;  
    struct Location *next;    // next location in list
};

struct Location* buildMap();  
void printMap(struct Location *head);
void addLocationNamed(struct Location **head, const char *newName,const char *connectName, int dist);

#endif
