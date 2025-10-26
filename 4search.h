#ifndef SEARCH_H
#define SEARCH_H

#include "5location.h"

struct Location* search(struct Location *head, const char *name);
void searchPrompt(struct Location *head);

#endif
