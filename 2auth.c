#include<stdio.h>
#include<string.h>
#include "5location.h"
#include "6navigation.h"
#include "4search.h"
#include "3record.h" 
#include "7gui.h"   

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

    if (!file) {
        printf("No user found. Please sign up first.\n");
        return;
    }

    fscanf(file, "%s %s", storedUser, storedPass);
    fclose(file);

    printf("Enter your username: ");
    scanf("%49s", inputUser);
    printf("Enter your password: ");
    scanf("%49s", inputPass);

    if (strcmp(storedUser, inputUser) == 0 && strcmp(storedPass, inputPass) == 0) {
        printf("Login successful! Welcome, %s.\n", inputUser);

        struct Location *campusMap = buildMap();

        // If you still want console menu, you can call:
        // navigationMenu(campusMap);

        // 🔥 But now launch GUI:
        launch_gui(campusMap);

    } else {
        printf("Login failed! Invalid username or password.\n");
    }
}
