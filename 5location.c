#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "5location.h"
// Find a location by name in the linked list
static struct Location* findLoc(struct Location *head, const char *name) {
    struct Location *cur = head;
    while (cur != NULL) {
        if (strcmp(cur->name, name) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

// Add a bidirectional connection between two locations
static void addConn(struct Location *head, const char *from, const char *to, int dist) {
    struct Location *loc1 = findLoc(head, from);
    struct Location *loc2 = findLoc(head, to);
    if (!loc1 || !loc2) return;

    struct AdjNode *c1 = malloc(sizeof(struct AdjNode));
    strcpy(c1->name, to);
    c1->distance = dist;
    c1->next = loc1->connections;
    loc1->connections = c1;

    struct AdjNode *c2 = malloc(sizeof(struct AdjNode));
    strcpy(c2->name, from);
    c2->distance = dist;
    c2->next = loc2->connections;
    loc2->connections = c2;
}

struct Location* buildMap() {
    struct Location *head = NULL, *temp;
    char *places[] = {
        "Gate1", "Gate2", "Gate3", "MainGround", "BTechBlock", "CSIT", 
        "ECEBlock", "MBABlock", "HappinessHut", "RaviCanteen", 
        "TuckShop", "Gate1Canteen", "BoysHostel", "GirlsHostel", 
        "Tunnel", "Library", "SportsComplex", "Auditorium", "Cafeteria",
        "AdminBlock", "MedicalCenter", "ParkingLot"
    };
    int n = sizeof(places)/sizeof(places[0]);

    for (int i = 0; i < n; i++) {
        temp = malloc(sizeof(struct Location));
        strcpy(temp->name, places[i]);
        temp->connections = NULL;
        temp->next = head;
        head = temp;
    }

    // Add connections (distances are approximate)
    addConn(head, "Gate1", "TuckShop", 1);
    addConn(head, "Gate1", "Gate1Canteen", 2);
    addConn(head, "Gate1", "MainGround", 3);
    addConn(head, "MainGround", "BTechBlock", 2);
    addConn(head, "MainGround", "RaviCanteen", 2);
    addConn(head, "MainGround", "BoysHostel", 3);
    addConn(head, "MainGround", "GirlsHostel", 3);
    addConn(head, "MainGround", "Library", 2);
    addConn(head, "BTechBlock", "HappinessHut", 2);
    addConn(head, "BTechBlock", "CSIT", 3);
    addConn(head, "CSIT", "ECEBlock", 2);
    addConn(head, "MBABlock", "AdminBlock", 2);
    addConn(head, "HappinessHut", "RaviCanteen", 1);
    addConn(head, "HappinessHut", "BoysHostel", 2);
    addConn(head, "BoysHostel", "Tunnel", 2);
    addConn(head, "Tunnel", "Gate2", 2);
    addConn(head, "Gate2", "CSIT", 3);
    addConn(head, "CSIT", "RaviCanteen", 2);
    addConn(head, "Library", "Auditorium", 1);
    addConn(head, "Library", "Cafeteria", 2);
    addConn(head, "SportsComplex", "BoysHostel", 3);
    addConn(head, "SportsComplex", "GirlsHostel", 3);
    addConn(head, "MedicalCenter", "AdminBlock", 2);
    addConn(head, "ParkingLot", "Gate3", 2);
    addConn(head, "Gate3", "MBABlock", 3);

    return head;
}

void printMap(struct Location *head) {
    struct Location *cur = head;
    while (cur != NULL) {
        printf("\n%s connects to:\n", cur->name);
        struct AdjNode *conn = cur->connections;
        while (conn != NULL) {
            printf("  %s (%d)\n", conn->name, conn->distance);
            conn = conn->next;
        }
        cur = cur->next;
    }
}
void findShortestPath(struct Location *head, const char *start, const char *dest) {
    printf("\nShortest path feature coming soon!\n");
}
