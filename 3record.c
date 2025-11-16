#include <stdio.h>
#include "5location.h"
#include "4search.h"
#include "6navigation.h"


void navigationMenu(struct Location *campusMap){
    int attChoice;
    do {
        printf("\n===== NAVIGATION SYSTEM =====\n");
        printf("1. Search Location\n");
        printf("2. Show All Locations\n");
        printf("3. Find Route Between Two Locations\n");
        printf("4. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &attChoice);

        switch(attChoice) {
             case 1:
                searchPrompt(campusMap);   // pass the location map
                break;
            case 2:
                printMap(campusMap);       // show all connected locations
                break;
            case 3: {
                char start[50], dest[50];
                printf("Enter starting location: ");
                scanf("%49s", start);
                printf("Enter destination location: ");
                scanf("%49s", dest);
                findShortestPath(campusMap, start, dest);
                break;
            }
            case 4:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while(attChoice != 4);
}
