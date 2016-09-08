#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Command line argument error!\n");
        return 1;
    }
    string pt;
    int pt_len, i, k_len, k = 0;
    k_len = strlen(argv[1]);
    for(i = 0; i < k_len; i++)
        k = k * 10 + argv[1][i] - '0';
        
    k = k % 26;
    pt = GetString();
    pt_len = strlen(pt);
    
    for(i = 0; i < pt_len; i++) {
        if(pt[i] >= 'a' && pt[i] <= 'z')
            pt[i] = 'a' + ((pt[i] - 'a') + k) % 26;
        else if(pt[i] >= 'A' && pt[i] <= 'Z')
            pt[i] = 'A' + ((pt[i] - 'A') + k) % 26;
    }
    printf("%s\n", pt);
    return 0;
}