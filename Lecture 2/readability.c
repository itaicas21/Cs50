#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main (void){
    string text = get_string("Input Text\n");
    int text_length = strlen(text), word_count=1, sentence_count=0, letter_count=0;
    float index;
    for (int i=0;i<text_length;i++){
        if (((int)text[i]>64&&(int)text[i]<91)||((int)text[i]>96&&(int)text[i]<123)) letter_count++;
        if (text[i]==' ') word_count++;
        if (text[i]=='.'||text[i]=='?'||text[i]=='!') sentence_count++;
    }
    index=round(0.0588*(((float)letter_count/word_count)*100)-0.296*(((float)sentence_count/word_count)*100)-15.8);
    if (index <1) {
    printf("Before Grade 1\n");
    } else if (index>16){
        printf("Grade 16+\n");
    } else printf("Grade %i\n",(int)index);
}