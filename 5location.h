#ifndef LOCATION_H
#define LOCATION_H

struct Location {
    char name[30];
    struct Location *next;
};

#endif
