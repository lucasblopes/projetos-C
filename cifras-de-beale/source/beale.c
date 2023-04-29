#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "../include/decode.h"
#include "../include/encode.h"
#include "../include/keys.h"

FILE* open_file(char* directory, char* mode) {

    FILE* file = fopen(directory, mode);

    if (!file) {
        perror("Error opening file");
        exit (1);
    }

    return file;
}

int main (int argc, char **argv) {

    struct charList* charlist = new_charlist();

    char *value_b = NULL;
    char *value_m = NULL;
    char *value_o = NULL;
    char *value_i = NULL;
    char *value_c = NULL;
    int flag_b = 0;
    int flag_d = 0;
    int flag_e = 0;
    int option;
 
    FILE* original_msg;
    FILE* cipher_book;
    FILE* key_file;
    FILE* coded_msg;

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

        original_msg = open_file(value_m, "r");
        cipher_book = open_file(value_b, "r");
        key_file = open_file(value_c, "w");
        coded_msg = open_file(value_o, "w");

        create_keylist_book(cipher_book, charlist);
        encode(original_msg, coded_msg, charlist);
        create_keyfile(key_file, charlist);

        fclose(original_msg);
        fclose(cipher_book);
        fclose(key_file);
        fclose(coded_msg);
    }


    if (flag_d) {

        coded_msg = open_file(value_i, "r");
        original_msg = open_file(value_o, "w");
        if (flag_b) {
            
            cipher_book = open_file(value_b, "r");
            create_keylist_book(cipher_book, charlist);
            fclose(cipher_book);
        } else {
            
            key_file = open_file(value_c, "r");
            create_keylist_file(key_file, charlist);
            fclose(key_file);
        }
        decode(coded_msg, original_msg, charlist);
        fclose(original_msg);
        fclose(coded_msg);
    }
    
    /* libera memoria alocada */
    free_charlist(charlist->head);
    free(charlist);
    charlist = NULL;

    return 0;
}