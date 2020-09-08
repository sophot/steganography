// #include <stdio.h>
#include "copyBMP.c"

int sizeOfInput(char* arg);
int getBMPFileSize(FILE* file);
int Encrypt(char* content);



int sizeOfInput(char* arg){
    int ans = 0;
    for(char* c = arg; *c != '\0'; c++){
        ans++;
    }
    return ans;
}

int getBMPFileSize(FILE* file){
    unsigned int size;
    fseek(file, 0x2, SEEK_SET);
    fread(&size, sizeof(int), 1, file);

    return size;
}

int Encrypt(FILE* original, char* content){
    FILE* stego = fopen("./stego.bmp", "wb");
    copyBMP(original, stego);
    
    

    fclose(stego);
}
