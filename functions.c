#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//The additional libraries are time.h, which is used to contain time
//and date function declaration to provide standardized access to
//time/date manipulation and formatting,
//math.h for basic mathematical operations and string.h which makes
// the use of string related functions possible such as strlen, strcat, strchr and so on.
#include "functions.h"

int prime_check(int num){
    //Checks if a given number is prime.
    //Returns 1 if it is otherwise 0.
    int prime=1;
    int i;

    if(num==0 || num==1)
        return 0;

    for(i=2; i<=num/2; i++)
        if(num%i==0)
            prime=0;

    return prime;
}

int number_generator(int max_num,int num_type){

    //If num_type==0 ->  generates a number that is not prime.
    //If num_type==1 ->  generates a prime number.
    //If num_type diferit de 0, 1 -> any number.
    //Any number = 1, 2, ... , max_num.

    srand(rand());
    int generated_num;
    int prime_vec_num[]={2,3,5,7,11,13,17,19,23,29};

      if(num_type==0){
        generated_num = (rand() % max_num)+1;
        if(prime_check(generated_num)!=0)
            return number_generator(max_num, num_type);
    }

    if(num_type==1){
       generated_num = (rand() % 10);
        generated_num = prime_vec_num[generated_num];
        if(generated_num>max_num)
            return number_generator(max_num, num_type);
    }

    if(num_type!=0 && num_type!=1){
        generated_num = (rand() % max_num)+1;
    }


    return generated_num;
}

char letter_generator(int letter_type, char excone, char exctwo){
    // Daca ce_fel_litera == 0 -> litera mica
    // Daca ce_fel_litera == 1 -> litera mare
    // In alt caz -> orice litera nu conteaza
            // E nevoie de excone si exctwo, ca sa poate fi
            // decriptat, pt ca daca nu ar fi, s-ar putea sa apara
            // aceeasi litera si ca litera esentiala, si ca litera
            // random, si asta ar da peste cap nr de litere esentiale.

    char letter;

    letter = number_generator(26, -1) + 64;

    if(letter_type==0)
        letter+=32;

    if(letter_type!=0 && letter_type!=1)
    {
        letter_type=number_generator(2,-1)-1;
        letter = letter_generator(letter_type, excone, exctwo);
    }

    if(letter==excone || letter==exctwo)
        return letter_generator(letter_type, excone, exctwo);

    return letter;
}

char* word_encrypter(char* word){
    char encrypted_word[1000]="";
    char letter;
    int i, j, k;
    int num_random_letters;
    int num_same_letters;

    for(i=0; i<strlen(word); i++)
    {
        num_same_letters = number_generator(6, 1);
        for(k=1; k<=num_same_letters; k++)
            encrypted_word[strlen(encrypted_word)]=word[i];

        num_random_letters = number_generator(2, -1);
        for(j=1; j<=num_random_letters; j++)
        {
            num_same_letters = number_generator(6, 0);
            letter=letter_generator(-1, word[i], word[i+1]);
            for(k=1; k<=num_same_letters; k++)
               encrypted_word[strlen(encrypted_word)]=letter;
        }
    }

    word=encrypted_word;
    return word;
}

char* text_encrypter(char* text){
    char encrypted_text[1000]="";
    char separators[20]=" ,.;:!?-\0";
    char word[1000]="";
    int i;

    for(i=0; i<=strlen(text); i++)
    {
        if(strchr(separators, text[i]) != NULL)
        {
            word[strlen(word)]='\0';
            strcat(encrypted_text, word_encrypter(word));
            encrypted_text[strlen(encrypted_text)]=text[i];
            memset(word,0,strlen(word));
        }else{
            word[strlen(word)]=text[i];
        }
    }

    text = encrypted_text;
    return text;
}

char* word_decrypter(char* word){
    char decrypted_word[1000]="";
    char letter = word[0];
    int app_num=0;
    int i;

    for(i=0; i<=strlen(word); i++)
    {
        if(word[i]==letter){
            app_num+=1;
        }else{
            if(prime_check(app_num)==1)
                decrypted_word[strlen(decrypted_word)]=letter;

            app_num=1;
            letter=word[i];
        }
    }

    word=decrypted_word;
    return word;
}

char* text_decrypter(char* text){
    char decrypted_text[1000]="";
    char separators[20]=" ,.;:!?-\0";
    char word[1000]="";
    int i;

    for(i=0; i<=strlen(text); i++)
    {
        if(strchr(separators, text[i]) != NULL)
        {
            word[strlen(word)]='\0';
            strcat(decrypted_text, word_decrypter(word));
            decrypted_text[strlen(decrypted_text)]=text[i];
            memset(word,0,strlen(word));
        }else{
            word[strlen(word)]=text[i];
        }
    }

    text = decrypted_text;
    return text;
}
