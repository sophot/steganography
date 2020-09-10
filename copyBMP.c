#include <stdio.h> 
#include <stdint.h>

typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;


typedef struct
{
    WORD h0;
    DWORD h1;
    WORD h2;
    WORD h3;
    DWORD h4;
    DWORD h5;
    LONG h6;
    LONG h7;
    WORD h8;
    WORD h9;
    DWORD h10;
    DWORD h11;
    LONG h12;
    LONG h13;
    DWORD h14;
    DWORD h15;
}BITMAPHEADER;

typedef struct
{
    BYTE red;
    BYTE green;
    BYTE blue;
}PIXEL;

void copyBMP(FILE* original, FILE* stego){

    // FILE *original, *stego;
    // original = fopen("./origin.bmp", "rb");
    // stego = fopen("./stego.bmp", "wb");
    // printf("%lu", sizeof(BITMAPFILEHEADER));

    BITMAPHEADER bf;
    fread(&bf, sizeof(BITMAPHEADER), 1, original);
    fwrite(&bf, sizeof(BITMAPHEADER), 1, stego);

    PIXEL pixel;

    while(1){
        //COPYING ORGINAL CONTENTS TO STEGO --RESULT IS CLOSE
        if ( fread(&pixel, sizeof(PIXEL), 1, original) < 1 )
            break;

        fwrite(&pixel, sizeof(PIXEL), 1, stego);
    }

    // fclose(stego);

    /*TO COMPENSATE THE LAST BYTE*/
    char nul = 0x00;
    // stego = fopen("./stego.bmp", "r+b");
    fseek(stego, 0x00, SEEK_END);
    fwrite(&nul, 1, 1, stego);
}