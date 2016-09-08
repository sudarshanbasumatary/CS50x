#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    int i;
    string name = GetString();
    putchar(toupper(name[0]));
    for(i = 0; i < strlen(name); i++)
        if(name[i] == ' ')
            putchar(toupper(name[i+1]));
    putchar(10);
}