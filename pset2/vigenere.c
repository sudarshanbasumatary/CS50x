#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Command line argument error!\n");
        return 1;
    }
    string pt, k;
    int pt_len, i, j, k_len;
    k = argv[1];
    k_len = strlen(k);
    for(i = 0; i < k_len; i++) {
        if(isalpha(k[i]) == false) {
            printf("Invalid key!\n");
            return 1;
        }
        if(k[i] >= 'A' && k[i] <= 'Z')
            k[i] = k[i] - 'A';
        else k[i] = k[i] - 'a';
    }
    pt = GetString();
    pt_len = strlen(pt);
    
    for(i = 0, j = 0; i < pt_len; i++) {
        if(isalpha(pt[i])) {
            if(pt[i] >= 'a' && pt[i] <= 'z')
                pt[i] = 'a' + ((pt[i] - 'a') + k[j]) % 26;
            else if(pt[i] >= 'A' && pt[i] <= 'Z')
                pt[i] = 'A' + ((pt[i] - 'A') + k[j]) % 26;
            j = (j + 1) % k_len;       
        }
    }
    printf("%s\n", pt);
    return 0;
}