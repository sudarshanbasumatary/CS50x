/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if(n > 0) {
        for(int i = 0; i < n; i++) 
            if(values[i] == value) 
                return true;
    } 
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int i, j, temp;
    // TODO: implement an O(n^2) sorting algorithm
    for(i = 0; i < n - 1; i++)
        for(j = i + 1; j < n; j++)
            if(values[i] > values[j]) {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
                
    return;
}