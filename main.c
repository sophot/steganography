// #include <stdio.h> 
#include <stdlib.h> //exit()
#include "Steganography.c"
#include "copyBMP.c"


int main(int argc, char *argv[]){
    //RECEIVE 2 CMD ARGUMENTS ONLY (1 -> exe file, 2 -> e or d)
  if(argc != 2){
      printf("Arguments do not match!\nRun again with './mystego.exe e' or './mystego.exe d'");
      exit(1);
  }

    //ASSIGN 2nd ARUGMENT TO MODE
  char *mode = argv[1];
    //CHECK IF ARGUMENT's(MODE) LENGTH IS NOT 1 CHARACTER
  if(sizeOfInput(mode) != 1){
      printf("Argument is too long!\nRun again with './mystego.exe e' or './mystego.exe d'");
      exit(1);
  }

    //ENCRYPTION
    if((*mode) == 'e'){
        /*
            Attempt: open original file to read and copy its content
                    to stego file. Then pass stego file to encrypt.
        */
        printf("Encryption Mode ON\n");
        char* content = "HELLO WORLD";
        FILE *original, *stego; 
    
        if((original = fopen("./origin.bmp", "rb")) == NULL){
            printf("Error opening \"origin.bmp\".\n");
            exit(1);
        }

        Encrypt(original, content);

        fclose(original);
    }

    // DECRYPTION
    if((*mode) == 'd'){
        printf("Decryption Mode ON\n");
        FILE *bmp;
        if((bmp = fopen("./stego.bmp", "rb")) == NULL){
            printf("Error opening \"stego.bmp\". MAKE SURE THE FILE EXIST!\n");
            exit(1);
        }

    }

    return 0;
}



