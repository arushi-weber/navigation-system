#include <stdio.h>
#include "7gui.h"  
#include "2auth.h"

int main() {
    int choice;

    do {
        printf("\n===========================================\n");
        printf("|         NAVIGATION PANEL - MENU         |\n");
        printf("===========================================\n");
        printf("|                                         |\n");
        printf("|   [1] >> Sign Up                        |\n");
        printf("|   [2] >> Login                          |\n");
        printf("|   [3] >> Exit                           |\n");
        printf("|                                         |\n");
        printf("===========================================\n");
        printf(">> Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                launch_gui(buildMap());   // login will launch GUI on success
                break;
            case 3:
                printf("Exit\n");
                break;
            default:
                printf("Enter a valid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
