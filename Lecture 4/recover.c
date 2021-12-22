#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;
bool isJpeg (BYTE buffer[]);

bool isJpeg (BYTE buffer[]) {
  if (buffer[0]==0xff&&buffer[1]==0xd8&&buffer[2]==0xff && (buffer[3] & 0xf0) == 0xe0) return true; //bitwise arithmatic on an 8 bit hexadecimal digit
  return false;
}

int main(int argc, char *argv[]) {
  if (argc!=2){
     printf("Only one argument allowed");
     return 1;
  }
  BYTE buffer [512];
  FILE *FATfile = fopen(argv[1],"r");
  int count = 0;
  char filename[10];
  bool isFirst = true;
  bool found = false;
  FILE *img=NULL;
  while (fread(buffer,sizeof(BYTE),512,FATfile)==512){
      if (isJpeg(buffer)){
        found=true;
        if (isFirst) {
          sprintf(filename,"%03i.jpg",count);
          img = fopen (filename,"w");
          fwrite(buffer,sizeof(BYTE),512,img);
          isFirst = false;
        } else {
          count++;
          fclose(img);
          sprintf(filename,"%03i.jpg",count);
          img = fopen (filename,"w");
          fwrite(buffer,sizeof(BYTE),512,img);
        }
      } else if (found==true) fwrite(buffer,sizeof(BYTE),512,img);

  }
  fclose(FATfile);
  fclose(img);
  return 0;
}