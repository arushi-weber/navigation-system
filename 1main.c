#include<stdio.h>
#include<string.h>
#include "2auth.c"
int main(){
    int choice;
    char loggedInUser[50] = "";
    do{
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
        
    scanf("%d",&choice);

    switch (choice){
    case 1: signUp(); break;
    case 2: login(); break;
    case 3: printf("Exit\n"); break;
    default: printf("Enter a Valid choice"); break;}
    }
    while(choice!=3);
    return 0;
}