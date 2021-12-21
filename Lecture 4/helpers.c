#include <math.h>
#include <stdlib.h>
#include "helpers.h"
// After implementing blur, i realized that its better to preserve the original data during the filtering process, thus persisting it.
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double avg;
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            avg = (image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3.0; // implicit casting by dividing by 3.0 - a double
            image[i][j].rgbtBlue=round(avg);
            image[i][j].rgbtRed=round(avg);
            image[i][j].rgbtGreen=round(avg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Can I implement more effeciently?
    BYTE temp;
    for (int i=0;i<height;i++){
        for (int j=0;(j-(width-1-j))<0;j++){


                temp = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue=image[i][width-1-j].rgbtBlue;
                image[i][width-1-j].rgbtBlue=temp;

                temp = image[i][j].rgbtRed;
                image[i][j].rgbtRed=image[i][width-1-j].rgbtRed;
                image[i][width-1-j].rgbtRed=temp;

                temp = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen=image[i][width-1-j].rgbtGreen;
                image[i][width-1-j].rgbtGreen=temp;

        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    float redSum,blueSum,greenSum,tempcount;
    int i,j;
    for (i=0;i<height;i++){
        for (j=0; j<width;j++){
            temp[i][j]=image[i][j];
        }
    }

    for (i=0;i<height;i++){
        for (j=0;j<width;j++){
            tempcount=redSum=blueSum=greenSum=0;
            // Try to avoid loop upon loop, instead , you can abstact the second 2d loop into a function, imporving readability.
            for (int n=i-1;n<i+2;n++){
                for (int m=j-1;m<j+2;m++){
                    if (n>=0&&n<height&&m>=0&&m<width){
                        tempcount++;
                        blueSum+=image[n][m].rgbtBlue;
                        greenSum+=image[n][m].rgbtGreen;
                        redSum+=image[n][m].rgbtRed;
                    }
                }
            }
            temp[i][j].rgbtBlue=round(blueSum/tempcount);
            temp[i][j].rgbtGreen=round(greenSum/tempcount);
            temp[i][j].rgbtRed=round(redSum/tempcount);
        }
    }
    for (i=0;i<height;i++){
        for (j=0; j<width;j++){
            image[i][j]=temp[i][j];
        }
    }
    return;
}

//Helper function for edges
int aboveRange(int xColor, int yColor){
    int result = round(sqrt((xColor*xColor)+(yColor*yColor)));
    if (result>255) return 255;
    return result;

}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Over Complicated index pointer counters (Declared too many variables) + Code Very Repetitive.
    // TODO Simpler index pointers.
    RGBTRIPLE temp[height][width];
    int GxRed,GxGreen,GxBlue,GyRed,GyGreen,GyBlue;
    int i,j;
    int GxCoordinates [3][3] = {
                                {-1,0,1},
                                {-2,0,2},
                                {-1,0,1}
                               };
    int GyCoordinates [3][3] = {
                                {-1,-2,-1},
                                {0,0,0},
                                {1,2,1}
                               };
    for (i=0;i<height;i++){
        for (j=0; j<width;j++){
            temp[i][j]=image[i][j];
        }
    }

     for (i=0;i<height;i++){
        for (j=0;j<width;j++){
            //Repititveness (what to do?)
            GxRed=GxGreen=GxBlue=GyRed=GyGreen=GyBlue=0;
            for (int n=i-1;n<i+2;n++){
                for (int m=j-1;m<j+2;m++){
                    if (n>=0&&n<height&&m>=0&&m<width){
                        GxRed += image[n][m].rgbtRed*GxCoordinates[n-i+1][m-j+1];
                        GxBlue += image[n][m].rgbtBlue*GxCoordinates[n-i+1][m-j+1];
                        GxGreen += image[n][m].rgbtGreen*GxCoordinates[n-i+1][m-j+1];
                        GyRed += image[n][m].rgbtRed*GyCoordinates[n-i+1][m-j+1];
                        GyBlue += image[n][m].rgbtBlue*GyCoordinates[n-i+1][m-j+1];
                        GyGreen += image[n][m].rgbtGreen*GyCoordinates[n-i+1][m-j+1];
                    }
                }
            }
            temp[i][j].rgbtRed = aboveRange(GxRed,GyRed);
            temp[i][j].rgbtGreen= aboveRange(GxGreen,GyGreen);
            temp[i][j].rgbtBlue= aboveRange(GxBlue,GyBlue);
        }
    }
    for (i=0;i<height;i++){
        for (j=0; j<width;j++){
            image[i][j]=temp[i][j];
        }
    }
    return;
}

