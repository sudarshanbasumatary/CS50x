#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    int coins = 0;
    float change;
    printf("O hai! ");
    do {
        printf("How much change is owed?\n");
        change = GetFloat();
    } while(change < 0);
    change = (int)round(change * 100);
    coins += change / 25;
    change = (int)change % 25;
    coins += change / 10;
    change = (int)change % 10;
    coins += change / 5;
    change = (int)change % 5;
    coins += change;
    
    printf("%d\n", coins);
}