#include<stdio.h>
#include<string.h>
#include "5location.h"
#include "4search.h"
#include "3record.h" 

void signUp(){
    char pass[50] , user[50];
    FILE *file =fopen("signup.txt","a");

    printf("Enter an username: ");
    scanf("%s", user);
    printf("Enter an password");
    scanf("%s",pass);
    fprintf(file,"%s %s\n",user,pass);
    fclose(file);
    printf("SignUp successfully! You can now login\n");
}
void login(){
    char storedUser[50], storedPass[50];
    char inputUser[50], inputPass[50];
    FILE *file = fopen("signup.txt", "r");

    fscanf(file, "%s %s", storedUser, storedPass);
    fclose(file);

    printf("Enter your username: \n");
    scanf("%s",inputUser);
    printf("Enter your password: \n");
    scanf("%s",inputPass);

    if (strcmp(storedUser, inputUser) == 0 && strcmp(storedPass, inputPass) == 0) {
        printf("Login successful! Welcome, %s.\n", inputUser);

        struct Location *campusMap = buildMap();

        // Optional: show the map to confirm
        printMap(campusMap);

        // Start navigation system with the map
        navigationMenu(campusMap);

    } else {
        printf("Login failed! Invalid username or password.\n");
    }
}