#include <stdio.h>
#include <cs50.h>

int main (void){
    int height = get_int("Enter Height\n");
    while (height<1||height>8){
        printf("Height must be between one and eight");
         height = get_int("Enter Height");
    }
    bool half;
    for (int i=0;i<height;i++){
        half = false;
        for(int j=0;j<height*2;j++){
            if (half==false) {
              if (j>=height-(i+1)){
                  printf("#");
              } else printf(" ");
            } else{
            if (j<=height+(i)) {
                printf("#");
            } else printf(" ");
            }
            if (j==height-1){
                half=true;
                printf("  ");
            }
        }
        printf("\n\n");
    }
}