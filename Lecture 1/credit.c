#include <stdio.h>
#include <cs50.h>

int main (void){
    long credit= get_long ("Enter credit card number\n");
    bool other_digit = false;
    int counter=0;
    int sum=0;
    int start;
    while (credit>0){
        if (credit<100&&credit>10) start=credit;
        if (!other_digit){
            sum += credit%10;
        } else {
            sum +=((credit%10*2)/10+(credit%10*2)%10);
        }
        credit= credit/10;
        counter++;
        other_digit=!other_digit;
    }
    if (counter==13&&sum%10==0) {
        printf("VISA\n");
    } else
    if (counter==15&&sum%10==0&&(start==37||start==34)) {
        printf("AMEX\n");

    } else
    if (counter==16&&sum%10==0) {
        if (start/10==4) {
            printf("VISA\n");

        } else if (start>50&&start<56) {
            printf("MASTERCARD\n");

        } else printf("INVALID\n");

    } else printf("INVALID\n");
}