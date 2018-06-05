#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "functions.h"

void main(){
    srand(time(NULL));

    char initial_text[1000]="";
    char text_encrypted[1000]="";
    char text_decrypted[1000]="";

    gets(initial_text);

    strcpy(text_encrypted, text_encrypter(initial_text));
    printf("\n%s\n", text_encrypted);

    strcpy(text_decrypted, text_decrypter(text_encrypted));
    printf("\n%s\n", text_decrypted);

    gets(initial_text);
}
