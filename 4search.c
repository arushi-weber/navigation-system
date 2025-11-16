#include <stdio.h>
#include <string.h>
#include "4search.h"
#include "6navigation.h"

struct Location* search(struct Location *head, const char *name) {
    struct Location *cur = head;
    while (cur != NULL) {
        if (strcmp(cur->name, name) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

void searchPrompt(struct Location *head) {
    char input[30];
    printf("\nEnter a location to search: ");
    scanf("%29s", input);

    struct Location *found = search(head, input);
    if (found)
        printf("Location '%s' exists in the campus.\n", found->name);
    else
        printf("Location '%s' not found in the campus.\n", input);
}
