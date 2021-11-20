#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[]){
    int num_of_times[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char key_char;
    if (argc==1) {
        printf ("No argument passed");
        return 1;
    }
    int str_len=strlen(argv[1]);
    if (str_len!=26) {
            printf("Key must contain 26 characters.\n");
            return 1;
    }
    for (int i=0;i<str_len;i++){
         key_char = toupper(argv[1][i]);
         if (key_char<65||key_char>90) {
            printf ("Not an Alphabetic letter");
            return 1;
           }
           num_of_times[key_char%65]++;
           if (num_of_times[key_char%65]>1){
               printf ("Duplicates");
               return 1;
           }
        }

    string plain = get_string("plaintext: ");
    str_len = strlen(plain);
    string cipher = plain;
    for(int i=0;i<str_len;i++){
        key_char=plain[i];
        if (key_char>64&&key_char<91){
        cipher[i]=toupper(argv[1][((int)key_char)%65]);
        } else if (key_char>96&&key_char<123){
            cipher[i]=tolower(argv[1][((int)key_char)%97]);
        }
    }
    printf("ciphertext: %s\n",cipher);
    return 0;

}