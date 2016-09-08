#include <cs50.h>
#include <stdio.h>

int main(void) {
    int minutes, bottles;
    printf("minutes: ");
    minutes = GetInt();
    
    bottles = 12 * minutes;
    printf("bottles: %d\n", bottles);
}