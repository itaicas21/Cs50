#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start = get_int("What is the start size? \n");
    while (start < 9){
        printf("Population must be larger than 9\n");
        start = get_int("What is the start size? \n");
    }


    // TODO: Prompt for end size
    int end = get_int("What is the end size? \n");
    while (end < start){
        printf("Population must be larger than the start\n");
        end = get_int("What is the end size? \n");
    }



    // TODO: Calculate number of years until we reach threshold
    int growth=start;
    int years = 0;
    while (growth<end){
        growth = growth+(growth/3-growth/4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i", years);
}