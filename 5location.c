#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "5location.h"

static struct Location* createLocation(char *name) {
    struct Location *loc = malloc(sizeof(struct Location));
    strcpy(loc->name, name);
    loc->connections = NULL;
    loc->next = NULL;
    return loc;
}

static void addConnection(struct Location *loc, char *to, int dist) {
    struct AdjNode *conn = malloc(sizeof(struct AdjNode));
    strcpy(conn->name, to);
    conn->distance = dist;
    conn->next = loc->connections;
    loc->connections = conn;
}

struct Location* buildMap() {

    // Create ALL updated locations
    struct Location *GATE1 = createLocation("GATE1");
    struct Location *TUCKSHOP = createLocation("TUCKSHOP");
    struct Location *GATE1CANTEEN = createLocation("GATE1CANTEEN");
    struct Location *MAINGROUND = createLocation("MAINGROUND");
    struct Location *BTECHBLOCK = createLocation("BTECHBLOCK");
    struct Location *ARYABHATTALAB = createLocation("ARYABHATTALAB");
    struct Location *PARAMLAB = createLocation("PARAMLAB");
    struct Location *PETROLEUMBLOCK = createLocation("PETROLEUMBLOCK");
    struct Location *HOTELMANAGEMENTBLOCK = createLocation("HOTELMANAGEMENTBLOCK");
    struct Location *OLDMCABLOCK = createLocation("OLDMCABLOCK");
    struct Location *CHANAKYABLOCK = createLocation("CHANAKYABLOCK");
    struct Location *MECHANICALBLOCK = createLocation("MECHANICALBLOCK");
    struct Location *DIGITALLAB = createLocation("DIGITALLAB");
    struct Location *BASKETBALLCOURT = createLocation("BASKETBALLCOURT");
    struct Location *BIOTECHBLOCK = createLocation("BIOTECHBLOCK");
    struct Location *CIVILBLOCK = createLocation("CIVILBLOCK");
    struct Location *HAPPINESSHUT = createLocation("HAPPINESSHUT");
    struct Location *RAVICANTEEN = createLocation("RAVICANTEEN");
    struct Location *BOYSHOSTEL = createLocation("BOYSHOSTEL");
    struct Location *TUNNEL = createLocation("TUNNEL");
    struct Location *CSIT = createLocation("CSIT");
    struct Location *GATE2CANTEEN = createLocation("GATE2CANTEEN");
    struct Location *GATE2 = createLocation("GATE2");

    // Link all nodes in a sequence
    GATE1->next = TUCKSHOP;
    TUCKSHOP->next = GATE1CANTEEN;
    GATE1CANTEEN->next = MAINGROUND;
    MAINGROUND->next = BTECHBLOCK;
    BTECHBLOCK->next = ARYABHATTALAB;
    ARYABHATTALAB->next = PARAMLAB;
    PARAMLAB->next = PETROLEUMBLOCK;
    PETROLEUMBLOCK->next = HOTELMANAGEMENTBLOCK;
    HOTELMANAGEMENTBLOCK->next = OLDMCABLOCK;
    OLDMCABLOCK->next = CHANAKYABLOCK;
    CHANAKYABLOCK->next = MECHANICALBLOCK;
    MECHANICALBLOCK->next = DIGITALLAB;
    DIGITALLAB->next = BASKETBALLCOURT;
    BASKETBALLCOURT->next = BIOTECHBLOCK;
    BIOTECHBLOCK->next = CIVILBLOCK;
    CIVILBLOCK->next = HAPPINESSHUT;
    HAPPINESSHUT->next = RAVICANTEEN;
    RAVICANTEEN->next = BOYSHOSTEL;
    BOYSHOSTEL->next = TUNNEL;
    TUNNEL->next = CSIT;
    CSIT->next = GATE2CANTEEN;
    GATE2CANTEEN->next = GATE2;

    // Add all connections with distances
    addConnection(GATE1, "TUCKSHOP", 25);
    addConnection(TUCKSHOP, "GATE1", 25);
    addConnection(TUCKSHOP, "GATE1CANTEEN", 25);
    addConnection(GATE1CANTEEN, "TUCKSHOP", 25);
    addConnection(GATE1CANTEEN, "MAINGROUND", 80);
    addConnection(MAINGROUND, "GATE1CANTEEN", 80);
    addConnection(MAINGROUND, "BTECHBLOCK", 50);
    addConnection(BTECHBLOCK, "MAINGROUND", 50);
    addConnection(BTECHBLOCK, "HAPPINESSHUT", 54);
    addConnection(HAPPINESSHUT, "BTECHBLOCK", 54);
    addConnection(HAPPINESSHUT, "RAVICANTEEN", 23);
    addConnection(RAVICANTEEN, "HAPPINESSHUT", 23);
    addConnection(RAVICANTEEN, "TUNNEL", 90);
    addConnection(TUNNEL, "RAVICANTEEN", 90);
    addConnection(TUNNEL, "CSIT", 60);
    addConnection(CSIT, "TUNNEL", 60);

    addConnection(BTECHBLOCK, "ARYABHATTALAB", 55);
    addConnection(ARYABHATTALAB, "BTECHBLOCK", 55);
    addConnection(ARYABHATTALAB, "PARAMLAB", 45);
    addConnection(PARAMLAB, "ARYABHATTALAB", 45);
    addConnection(PARAMLAB, "PETROLEUMBLOCK", 73);
    addConnection(PETROLEUMBLOCK, "PARAMLAB", 73);

    addConnection(PETROLEUMBLOCK, "HOTELMANAGEMENTBLOCK", 60);
    addConnection(HOTELMANAGEMENTBLOCK, "PETROLEUMBLOCK", 60);
    addConnection(HOTELMANAGEMENTBLOCK, "OLDMCABLOCK", 30);
    addConnection(OLDMCABLOCK, "HOTELMANAGEMENTBLOCK", 30);
    addConnection(OLDMCABLOCK, "CHANAKYABLOCK", 20);
    addConnection(CHANAKYABLOCK, "OLDMCABLOCK", 20);

    addConnection(CHANAKYABLOCK, "MECHANICALBLOCK", 100);
    addConnection(MECHANICALBLOCK, "CHANAKYABLOCK", 100);
    addConnection(CHANAKYABLOCK, "GATE2CANTEEN", 10);
    addConnection(GATE2CANTEEN, "CHANAKYABLOCK", 10);
    addConnection(GATE2CANTEEN, "GATE2", 115);
    addConnection(GATE2, "GATE2CANTEEN", 115);

    addConnection(PARAMLAB, "DIGITALLAB", 25);
    addConnection(DIGITALLAB, "PARAMLAB", 25);

    addConnection(ARYABHATTALAB, "MECHANICALBLOCK", 80);
    addConnection(MECHANICALBLOCK, "ARYABHATTALAB", 80);

    addConnection(BASKETBALLCOURT, "BIOTECHBLOCK", 15);
    addConnection(BIOTECHBLOCK, "BASKETBALLCOURT", 15);

    addConnection(BIOTECHBLOCK, "CIVILBLOCK", 52);
    addConnection(CIVILBLOCK, "BIOTECHBLOCK", 52);

    addConnection(MAINGROUND, "BOYSHOSTEL", 106);
    addConnection(BOYSHOSTEL, "MAINGROUND", 106);

    addConnection(HAPPINESSHUT, "BOYSHOSTEL", 100);
    addConnection(BOYSHOSTEL, "HAPPINESSHUT", 100);

    addConnection(GATE1, "CSIT", 300);
    addConnection(CSIT, "GATE1", 300);

    addConnection(GATE1, "GATE2", 415);
    addConnection(GATE2, "GATE1", 415);

    addConnection(MAINGROUND, "HAPPINESSHUT", 120);
    addConnection(HAPPINESSHUT, "MAINGROUND", 120);

    addConnection(BTECHBLOCK, "PARAMLAB", 60);
    addConnection(PARAMLAB, "BTECHBLOCK", 60);

    addConnection(CIVILBLOCK, "BTECHBLOCK", 85);
    addConnection(BTECHBLOCK, "CIVILBLOCK", 85);

    return GATE1;
}

void printMap(struct Location *head) {
    struct Location *temp = head;

    printf("\n====== CAMPUS MAP ======\n");

    while (temp != NULL) {
        printf("%s -> ", temp->name);

        struct AdjNode *conn = temp->connections;
        while (conn != NULL) {
            printf("%s(%d) ", conn->name, conn->distance);
            conn = conn->next;
        }
        printf("\n");

        temp = temp->next;
    }

    printf("========================\n");
}
