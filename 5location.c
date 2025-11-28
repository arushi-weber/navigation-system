#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "5location.h"

/* creates a location node */
static struct Location* createLocation(const char *name) {
    struct Location *n = malloc(sizeof(struct Location));
    strcpy(n->name, name);
    n->connections = NULL;
    n->next = NULL;
    return n;
}

/* adds connection for a location */
static void addConnection(struct Location *loc, const char *to, int dist) {
    struct AdjNode *a = malloc(sizeof(struct AdjNode));
    strcpy(a->name, to);
    a->distance = dist;
    a->next = loc->connections;
    loc->connections = a;
}

/* adds new place + builds two-way connection */
void addLocationNamed(struct Location **head,
                      const char *newName,
                      const char *connectName,
                      int dist) {

    /* create the node */
    struct Location *newLoc = createLocation(newName);

    /* add at start of list */
    newLoc->next = *head;
    *head = newLoc;

    /* find the place to connect with */
    struct Location *t = *head;
    while (t && strcmp(t->name, connectName) != 0)
        t = t->next;

    if (!t) return;

    /* add two-way links */
    addConnection(newLoc, connectName, dist);
    addConnection(t, newName, dist);
}

/* create the full campus map */
struct Location* buildMap() {

    /* make nodes */
    struct Location *GATE1 = createLocation("GATE1");
    struct Location *TUCK = createLocation("TUCKSHOP");
    struct Location *CANTEEN = createLocation("GATE1CANTEEN");
    struct Location *GROUND = createLocation("MAINGROUND");
    struct Location *BTECH = createLocation("BTECHBLOCK");
    struct Location *ARYA = createLocation("ARYABHATTALAB");
    struct Location *PARAM = createLocation("PARAMLAB");
    struct Location *DIGITAL = createLocation("DIGITALLAB");
    struct Location *BB = createLocation("BASKETBALLCOURT");
    struct Location *CIVIL = createLocation("CIVILBLOCK");
    struct Location *HH = createLocation("HAPPINESSHUT");
    struct Location *RAVI = createLocation("RAVICANTEEN");
    struct Location *HOSTEL = createLocation("BOYSHOSTEL");
    struct Location *TUNNEL = createLocation("TUNNEL");
    struct Location *CSIT = createLocation("CSIT");
    struct Location *PETRO = createLocation("PETROLEUMBLOCK");
    struct Location *HM = createLocation("HOTELMANAGEMENT");
    struct Location *OLDMCA = createLocation("OLDMCABLOCK");
    struct Location *CHANAKYA = createLocation("CHANAKYABLOCK");
    struct Location *GATE2C = createLocation("GATE2CANTEEN");
    struct Location *GATE2 = createLocation("GATE2");

    /* build linked list of all locations */
    GATE1->next = TUCK;
    TUCK->next = CANTEEN;
    CANTEEN->next = GROUND;
    GROUND->next = BTECH;
    BTECH->next = ARYA;
    ARYA->next = PARAM;
    PARAM->next = DIGITAL;
    DIGITAL->next = BB;
    BB->next = CIVIL;
    CIVIL->next = HH;
    HH->next = RAVI;
    RAVI->next = HOSTEL;
    HOSTEL->next = TUNNEL;
    TUNNEL->next = CSIT;
    CSIT->next = PETRO;
    PETRO->next = HM;
    HM->next = OLDMCA;
    OLDMCA->next = CHANAKYA;
    CHANAKYA->next = GATE2C;
    GATE2C->next = GATE2;

    struct Location *head = GATE1;

    /* add distances (two-way graph links) */
    addConnection(GATE1, "TUCKSHOP", 25);
    addConnection(TUCK, "GATE1CANTEEN", 25);
    addConnection(CANTEEN, "MAINGROUND", 80);
    addConnection(GROUND, "BTECHBLOCK", 50);
    addConnection(BTECH, "ARYABHATTALAB", 55);
    addConnection(ARYA, "PARAMLAB", 45);
    addConnection(PARAM, "DIGITALLAB", 25);
    addConnection(PARAM, "BASKETBALLCOURT", 35);
    addConnection(BB, "CIVILBLOCK", 52);
    addConnection(CIVIL, "HAPPINESSHUT", 75);
    addConnection(HH, "RAVICANTEEN", 23);
    addConnection(BTECH, "HAPPINESSHUT", 54);
    addConnection(GROUND, "BOYSHOSTEL", 106);
    addConnection(HOSTEL, "TUNNEL", 50);
    addConnection(TUNNEL, "CSIT", 60);
    addConnection(GATE1, "CSIT", 100);

    addConnection(PARAM, "PETROLEUMBLOCK", 73);
    addConnection(PETRO, "HOTELMANAGEMENT", 60);
    addConnection(HM, "OLDMCABLOCK", 30);
    addConnection(OLDMCA, "CHANAKYABLOCK", 20);
    addConnection(CHANAKYA, "GATE2CANTEEN", 10);
    addConnection(CHANAKYA, "BTECHBLOCK", 100);
    addConnection(GATE2C, "GATE2", 115);
    addConnection(GATE2, "GATE1", 415);

    return head;
}

/* print map in terminal */
void printMap(struct Location *head) {
    struct Location *t = head;

    while (t) {
        printf("%s -> ", t->name);

        struct AdjNode *c = t->connections;
        while (c) {
            printf("%s(%dm) ", c->name, c->distance);
            c = c->next;
        }
        printf("\n");
        t = t->next;
    }
}
