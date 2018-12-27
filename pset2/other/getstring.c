#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char name[20];
    char ID[10];
    printf("name: ");
    fgets(name, sizeof(name) + 1, stdin);
    printf("your name is: %s\n", name);
    printf("ID: ");
    fgets(ID, sizeof(ID) + 1, stdin);
    printf("your name is now: %s\n", name);
    printf("your ID is: %s\n", ID);
    return 0;
}