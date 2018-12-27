#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <unistd.h>

int main(void)
{
    printf("enter your password: ");
    string key = get_string();

    printf("enter your salt: ");
    string salt = get_string();

    string hash = crypt(key, salt);
    printf("hash is: %s\n", hash);
}