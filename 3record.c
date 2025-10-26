#include <stdio.h>
#include "5location.h"
#include "4search.h"

void navigationMenu(struct Location *head) {
    int attChoice;
    do {
        printf("\n===== NAVIGATION SYSTEM =====\n");
        printf("1. Search Location\n");
        printf("4. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &attChoice);

        switch(attChoice) {
            case 1:
                searchPrompt(head);
                break;
            case 4:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while(attChoice != 4);
}
