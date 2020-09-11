#include "copyBMP.c"

//HELPER FUNCTIONS
int getStrLength(char *str){
    //RETURN LENGTH OF A STRING
    int i  = 0;
    for(i = 0; str[i] != '\n'; i++);
    return i;
}
int sizeOfInputMode(char* arg){
    //COUNT Size of INPUT MODE
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
//END HELPER FUNCTIONS


int Encode(FILE* original, char* content){
    if((original = fopen("./origin.bmp", "rb")) == NULL){
        printf("Error opening \"origin.bmp\".\n");
        return -1;
    }
    //IF FILE NOT EXIST, CREATE NEW FILE
    FILE* stego = fopen("./stego.bmp", "wb");
    copyBMP(original, stego);
    fclose(stego);

    stego = fopen("./stego.bmp", "r+b");

    //SAVE LENGTH OF CONTENT TO FILE AT 0x33 (4BYTES)
    int content_len = getStrLength(content);
    fseek(stego, 0x2D, SEEK_SET);
    fwrite(&content_len, sizeof(int), 1, stego);

    int idx = 0;
    for(int i = 0; i < getStrLength(content)*2; i+=2){ //loop through encrypting content
        char cont = content[idx++]; char origH, origL, low, high; 

        fseek(stego, 0x36 + (3*i), SEEK_SET); // SEEK TO LOWER
        fread(&origL, 1, 1, stego);
        fseek(stego, 0x36 + (3*i) +3 , SEEK_SET); // SEEK TO HIGHER
        fread(&origH, 1, 1, stego);

        //GET LOW and HIGH HALF BYTE OF A CHARACTER
        low = cont & 0x0F;
        high = cont >> 4;

        //PUT LOW and HIGH IN STEGANO
        char steL = (origL & 0xF0) | low;
        char steH = (origH & 0xF0) | high;

        fseek(stego, 0x36 + (3*i), SEEK_SET); //seek to put low in stego
        fwrite(&steL, 1, 1, stego);
        fseek(stego, 0x36 + (3*i) + 3, SEEK_SET); //seek to put high in stego
        fwrite(&steH, 1, 1, stego);
    }
    fclose(stego);
    return 1;
}
int Decode(FILE* stego){
    if((stego = fopen("./stego.bmp", "rb")) == NULL){
        printf("Error opening \"stego.bmp\". MAKE SURE THE FILE EXIST!\n");
        return -1;
    }
    int content_len;

    //READ LENGTH OF CONTENT TO DECRYPT
    fseek(stego, 0x2D, SEEK_SET);
    fread(&content_len, sizeof(int), 1, stego);

    for(int i = 0; i < content_len*2; i+=2){
        
        char low;
        char high;
        fseek(stego, 0x36 + (3*i), SEEK_SET);
        fread(&low, sizeof(char), 1, stego);
        fseek(stego, 0x36 + (3*i) + 3, SEEK_SET);
        fread(&high, sizeof(char), 1, stego);


        high = high << 4;
        low = low & 0x0F;
        high = high | low;
        printf("%c", high);
    }
    printf("\n\nDecoded %d characters\n", content_len);
    fclose(stego);
    return 1;
}
