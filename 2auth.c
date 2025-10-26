#include<stdio.h>
#include<string.h>
#include "5location.h"
#include "4search.c"
#include "3record.c"
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

        //small sample of location to test search module
        struct Location a = {"Library", NULL};
        struct Location b = {"Canteen", NULL};
        struct Location c = {"Lab", NULL};
        a.next = &b;
        b.next = &c;

        navigationMenu(&a);

    } else {
        printf("Login failed! Invalid username or password.\n");
    }
}