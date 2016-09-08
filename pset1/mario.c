#include <cs50.h>
#include <stdio.h>

int main() {
    int height, i, j;
    do {
        printf("Height: ");
        height = GetInt();
    }
    while(height < 0 || height > 23);
    for(i = 0; i < height; i++) {
        for(j = 0; j < height - i - 1; j++)
            putchar(' ');
        for(j = 0; j < i + 2; j++)
            putchar('#');
        putchar(10);
    }
}