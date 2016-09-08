/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

void itoa(int num, char *imgName) {
    if(num < 10) {
        imgName[0] = '0';
        imgName[1] = '0';
        imgName[2] = '0' + num;
    }
    else if(num < 100) {
        imgName[0] = '0';
        imgName[1] = '0' + num / 10;
        imgName[2] = '0' + num % 10;
    }
    else {
        imgName[0] = '0' + num / 100;
        imgName[1] = '0' + (num / 10) % 10;
        imgName[2] = '0' + num % 10;
    }
    imgName[3] = '\0';
}

int main(int argc, char* argv[])
{
    int imgCount = 0;
    FILE *raw = fopen("card.raw", "r"), *img = NULL;
    char imgName[4];
    BYTE jpeg_block512[64];
    if(raw) {
        while(fread(jpeg_block512, sizeof(BYTE), 64, raw) == 64) {
            if(jpeg_block512[0] == 0xff 
                && jpeg_block512[1] == 0xd8 
                && jpeg_block512[2] == 0xff
                && jpeg_block512[3] >= 0xe0
            ) {
                if(img) {
                    fclose(img);
                    itoa(imgCount++, imgName);
                    strcat(imgName, ".jpg");
                    img = fopen(imgName, "w");
                }
                else {
                    itoa(imgCount++, imgName);
                    strcat(imgName, ".jpg");
                    img = fopen(imgName, "w");
                }
            }
            if(img)
                fwrite(jpeg_block512, sizeof(BYTE), 64, img);
        }
    }
    else {
        printf("Raw file read fail!");
        return 1;
    }
}
