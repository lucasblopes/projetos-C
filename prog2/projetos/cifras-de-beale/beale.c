#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>

#include "decode.h"
#include "encode.h"
#include "keys.h"

/* TAREFAS
 organizar openfile/ closefile
 fazer funcoes free
*/

FILE* openFile(char* directory, char* mode) {

    FILE* file = fopen(directory, mode);

    if (!file) {
        perror("Error opening file");
        exit (1);
    }

    return file;
}

int main (int argc, char **argv) {

    struct charList* charlist = newCharList();

    char *value_e = NULL;
    char *value_b = NULL;
    char *value_m = NULL;
    char *value_o = NULL;
    char *value_i = NULL;
    char *value_c = NULL;
    int flag_b = 0;
    int flag_d = 0;
    int flag_e = 0;
    int option;
 
    FILE* originalMsg;
    FILE* cipherBook;
    FILE* keyFile;
    FILE* codedMsg;

    while ((option = getopt (argc, argv, "edb:i:m:o:c:")) != -1) {
        switch (option) {
            case 'e':       
                flag_e = 1;
                break;
            case 'd':       
                flag_d = 1;
                break;
            case 'b':       
                flag_b = 1;
                value_b = optarg;
                break;
            case 'i':
                value_i = optarg;
                break;
            case 'm':
                value_m = optarg;
                break;
            case 'o':
                value_o = optarg;
                break;
            case 'c':
                value_c = optarg;
                break;
        default:
            fprintf (stderr, "Usage: %s -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves \n", argv[0]);

            fprintf (stderr, "Usage: %s -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada \n", argv[0]);

            fprintf (stderr, "Usage: %s -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada \n", argv[0]);

	        exit (1);
        }   
    }
 
    
    if (flag_e) {

        originalMsg = openFile(value_m, "r");
        cipherBook = openFile(value_b, "r");
        keyFile = openFile(value_c, "w");
        codedMsg = openFile(value_o, "w");

        createKeyListFromBook(cipherBook, charlist);
        encode(originalMsg, codedMsg, charlist);
        createKeyFile(keyFile, charlist);

        fclose(originalMsg);
        fclose(cipherBook);
        fclose(keyFile);
        fclose(codedMsg);
    }


    if (flag_d) {

        codedMsg = openFile(value_i, "r");
        originalMsg = openFile(value_o, "w");
        if (flag_b) {
            
            cipherBook = openFile(value_b, "r");
            createKeyListFromBook(cipherBook, charlist);

            fclose(cipherBook);
        } else {
            
            keyFile = openFile(value_c, "r");
            createKeyListFromFile(keyFile, charlist);
        }
        decode(codedMsg, originalMsg, charlist);

        fclose(originalMsg);
        fclose(codedMsg);
    }
    

    return 0;
}