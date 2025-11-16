#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "5location.h"

// Old function: keeps printing to terminal (for CLI mode)
void findShortestPath(struct Location *head, const char *start, const char *end);

// New: fills a buffer so GUI can display the path
// returns 1 on success, 0 on failure
int findShortestPathToBuffer(struct Location *head,
                             const char *start,
                             const char *end,
                             char *outPath, int outSize,
                             int *outDistance);

#endif
