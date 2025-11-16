// 6navigation.h
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "5location.h"

// Dijkstra shortest path between two locations
void findShortestPath(struct Location *head, const char *start, const char *end);

#endif
