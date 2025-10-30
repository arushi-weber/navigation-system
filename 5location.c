#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "5location.h"

static struct Location* createLocation(char *name) {
    struct Location *loc = (struct Location*)malloc(sizeof(struct Location));
    strcpy(loc->name, name);
    loc->connections = NULL;
    loc->next = NULL;
    return loc;
}

static void addConnection(struct Location *loc, char *to, int dist) {
    struct AdjNode *conn = (struct AdjNode*)malloc(sizeof(struct AdjNode));
    strcpy(conn->name, to);
    conn->distance = dist;
    conn->next = loc->connections;
    loc->connections = conn;
}

struct Location* buildMap() {
    struct Location *gate1 = createLocation("Gate1");
    struct Location *tuckshop = createLocation("TuckShop");
    struct Location *canteen = createLocation("Gate1Canteen");
    struct Location *ground = createLocation("MainGround");
    struct Location *block = createLocation("BTechBlock");
    struct Location *hut = createLocation("HappinessHut");
    struct Location *ravi = createLocation("RaviCanteen");
    struct Location *hostel = createLocation("BoysHostel");
    struct Location *tunnel = createLocation("Tunnel");
    struct Location *csit = createLocation("CSIT");
    struct Location *gate2 = createLocation("Gate2");

    gate1->next = tuckshop;
    tuckshop->next = canteen;
    canteen->next = ground;
    ground->next = block;
    block->next = hut;
    hut->next = ravi;
    ravi->next = hostel;
    hostel->next = tunnel;
    tunnel->next = csit;
    csit->next = gate2;

    addConnection(gate1, "TuckShop", 1);
    addConnection(gate1, "Gate1Canteen", 2);
    addConnection(gate1, "MainGround", 3);

    addConnection(tuckshop, "Gate1", 1);

    addConnection(canteen, "Gate1", 2);
    addConnection(canteen, "BoysHostel", 3);

    addConnection(ground, "BTechBlock", 2);
    addConnection(ground, "RaviCanteen", 2);
    addConnection(ground, "Gate1", 3);

    addConnection(block, "MainGround", 2);
    addConnection(block, "HappinessHut", 2);
    addConnection(block, "CSIT", 3);

    addConnection(hut, "BTechBlock", 2);
    addConnection(hut, "RaviCanteen", 1);
    addConnection(hut, "BoysHostel", 2);

    addConnection(ravi, "HappinessHut", 1);
    addConnection(ravi, "MainGround", 2);

    addConnection(hostel, "Gate1Canteen", 3);
    addConnection(hostel, "HappinessHut", 2);
    addConnection(hostel, "Tunnel", 2);

    addConnection(tunnel, "BoysHostel", 2);
    addConnection(tunnel, "Gate2", 2);

    addConnection(csit, "BTechBlock", 3);
    addConnection(csit, "Gate2", 3);

    addConnection(gate2, "Tunnel", 2);
    addConnection(gate2, "CSIT", 3);

    return gate1;
}