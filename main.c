// #include <stdio.h> 
#include <stdlib.h> //exit()
#include "Steganography.c"
// #include "copyBMP.c"

#define MAX_LENGTH 65940


int main(int argc, char *argv[]){
    //RECEIVE 2 CMD ARGUMENTS ONLY (1 -> exe file, 2 -> e or d)
  if(argc != 2){
      printf("Arguments do not match!\nRun again with './mystego.exe e' or './mystego.exe d'");
      exit(1);
  }

    //ASSIGN 2nd ARUGMENT TO MODE
  char *mode = argv[1];
    //CHECK IF ARGUMENT's(MODE) LENGTH IS NOT 1 CHARACTER
  if(sizeOfInputMode(mode) != 1){
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
        //GET INPUT TO ENCRYPT
        char content[MAX_LENGTH];
        if(fgets(content, MAX_LENGTH, stdin) == 0){
            printf("sth wrong\n");
            exit(1);
        }

        FILE *original;
        Encrypt(original, content);
    }

    // DECRYPTION
    if((*mode) == 'd'){
        printf("Decryption Mode ON\n");
        FILE *stego;

        Decrypt(stego);
    }

    return 0;
}

/*
    Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularized in the 1960s with the release of Letrasetsheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
*/