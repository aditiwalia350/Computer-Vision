//
//  project2.c
//  Project2
//
//  Created by Aditi Walia on 10/13/20.
//  Copyright © 2020 Aditi Walia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "netpbm.h"
#include <stdio.h>
#include <time.h>
#include <float.h>
Matrix create_gaussian_filter(void);
void edgeDetection(char *inputFilename, char *sobelFilename, char *cannyFilename);
Matrix convolve(Matrix m1, Matrix m2);
Image sobel(Image img);
Matrix scale(Matrix m, double gamma);
Image canny(Image img);

//referred to https://www.geeksforgeeks.org/gaussian-filter-generation-c
Matrix create_gaussian_filter(){
    
    Matrix kernel = createMatrix(5, 5);
    double sigma = 1.0;
    double s = 2.0 * sigma * sigma;
    double sum = 0.0;
    for (int x = -2; x <= 2; x++)
    {
        for(int y = -2; y <= 2; y++)
           {
               kernel.map[x + 2][y + 2] = (exp(-(sqrt(x*x + y*y)*sqrt(x*x + y*y))/s))/(M_PI * s);
               sum += kernel.map[x + 2][y + 2];
           }
    }
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
               kernel.map[i][j] = kernel.map[i][j]/sum;
    return kernel;
}

void edgeDetection(char *inputFilename, char *sobelFilename, char *cannyFilename){
    char input_file_path[300] = "/Users/aditiwalia/Desktop/Project2/Project2/";
    char sobel_file_path[300] = "/Users/aditiwalia/Desktop/Project2/Project2/";
    char canny_file_path[150] = "/Users/aditiwalia/Desktop/Project2/Project2/";


    strcat(input_file_path,inputFilename);
    strcat(sobel_file_path, sobelFilename);
    strcat(canny_file_path, cannyFilename);
    Image inputImage = readImage(input_file_path);
    Matrix matrixImage = image2Matrix(inputImage);
    
    //smoothing averaging filter
    /*Matrix filter = createMatrix(5, 5);
    for(int i =0; i<5; i++){
        for(int j =0; j<5; j++){
            
            filter.map[i][j] = (double)1/25;
            
        }
    }*/
    
    Matrix filter = create_gaussian_filter();
    
    //smooth image
    Matrix test = convolve(matrixImage, filter);
    Image initial = matrix2Image(test, 0, 1.0);
    
    
    writeImage(initial, "/Users/aditiwalia/Desktop/Project2/Project2/smooth_output.pgm");
    Image output = sobel(initial);
    writeImage(output, sobel_file_path);
    Image output_2 = canny(initial);
    writeImage(output_2, canny_file_path);
    
}

int main(int argc, const char * argv[]) {

    edgeDetection("butterfly.pgm", "sobel.pgm", "canny.pgm");
    /*srand((unsigned int)time(NULL));
    Image inputImage = readImage("/Users/aditiwalia/Desktop/ProjectCV1/ProjectCV1/dog.pgm");
    Matrix matrixImage = image2Matrix(inputImage);
    Matrix matrixImage = createMatrix(6, 6);
    matrixImage.map[0][0]=220.0;
    matrixImage.map[0][1]=219.0;
    matrixImage.map[0][2]=183.0;
    matrixImage.map[0][3]=170.0;
    matrixImage.map[0][4]=120.0;
    matrixImage.map[0][5]=78.0;
    
    matrixImage.map[1][0]=209.0;
    matrixImage.map[1][1]=215.0;
    matrixImage.map[1][2]=200.0;
    matrixImage.map[1][3]=180.0;
    matrixImage.map[1][4]=131.0;
    matrixImage.map[1][5]=101.0;
    
    matrixImage.map[2][0]=211.0;
    matrixImage.map[2][1]=202.0;
    matrixImage.map[2][2]=182.0;
    matrixImage.map[2][3]=119.0;
    matrixImage.map[2][4]=87.0;
    matrixImage.map[2][5]=71.0;
    
    matrixImage.map[3][0]=176.0;
    matrixImage.map[3][1]=165.0;
    matrixImage.map[3][2]=121.0;
    matrixImage.map[3][3]=101.0;
    matrixImage.map[3][4]=100.0;
    matrixImage.map[3][5]=82.0;
    
    matrixImage.map[4][0]=100.0;
    matrixImage.map[4][1]=105.0;
    matrixImage.map[4][2]=90.0;
    matrixImage.map[4][3]=84.0;
    matrixImage.map[4][4]=119.0;
    matrixImage.map[4][5]=69.0;
    
    matrixImage.map[5][0]=79.0;
    matrixImage.map[5][1]=85.0;
    matrixImage.map[5][2]=97.0;
    matrixImage.map[5][3]=77.0;
    matrixImage.map[5][4]=75.0;
    matrixImage.map[5][5]=58.0;
    */
    
    /*Matrix matrixImage = createMatrix(5, 5);
    matrixImage.map[0][0]=0.0;
    matrixImage.map[0][1]=150.0;
    matrixImage.map[0][2]=0.0;
    matrixImage.map[0][3]=150.0;
    matrixImage.map[0][4]=0.0;
    
    matrixImage.map[1][0]=0.0;
    matrixImage.map[1][1]=150.0;
    matrixImage.map[1][2]=0.0;
    matrixImage.map[1][3]=150.0;
    matrixImage.map[1][4]=0.0;
    
    matrixImage.map[2][0]=0.0;
    matrixImage.map[2][1]=150.0;
    matrixImage.map[2][2]=0.0;
    matrixImage.map[2][3]=150.0;
    matrixImage.map[2][4]=0.0;
    
    matrixImage.map[3][0]=0.0;
    matrixImage.map[3][1]=150.0;
    matrixImage.map[3][2]=0.0;
    matrixImage.map[3][3]=150.0;
    matrixImage.map[3][4]=0.0;
    
    matrixImage.map[4][0]=0.0;
    matrixImage.map[4][1]=150.0;
    matrixImage.map[4][2]=0.0;
    matrixImage.map[4][3]=150.0;
    matrixImage.map[4][4]=0.0;
    
    
    Matrix filter = createMatrix(5, 5);
    for(int i =0; i<5; i++){
        for(int j =0; j<5; j++){
            
            filter.map[i][j] = (double)1/25;
            
        }
    }
    Matrix test = convolve(matrixImage, filter);
    
    Image initial = matrix2Image(test, 0, 1.0);
    writeImage(initial, "/Users/aditiwalia/Desktop/ProjectCV1/ProjectCV1/smooth_output.pgm");
    Image output = sobel(initial);
    writeImage(output, "/Users/aditiwalia/Desktop/ProjectCV1/ProjectCV1/smooth_sobel_output.pgm");
    Image output_2 = canny(initial);
    writeImage(output_2, "/Users/aditiwalia/Desktop/ProjectCV1/ProjectCV1/canny_output.pgm");
    */
    
}

//custom scaling code. discussed with harshit and yash
Matrix scale(Matrix input, double gamma){
    double max = -DBL_MAX;
    for(int x=0; x<input.height; x++){
        for(int y=0; y<input.width; y++){
            double val = (int)input.map[x][y];
            if (val > max)
                max = val;
     }
    }
    for(int x=0; x<input.height; x++){
        for(int y=0; y<input.width; y++){
            double val = input.map[x][y];
            input.map[x][y] = 255.0*pow((val)/(max),gamma);
        }
    }
    return input;
}


Matrix convolve(Matrix m1, Matrix m2){
    Matrix convolved = createMatrix(m1.height, m1.width);
    
    if(m2.height%2 != 0){
        int step_h = m2.height/2;
        int step_w = m2.width/2;
        for(int i=step_h; i<m1.height-1;i++){
            for(int j =step_w; j<m1.width-1;j++){
                int k =0, l =0;
                for(int height = i-step_h; height <=i + step_h ; height++){
                        for(int width = j - step_w; width <= j+step_w; width++){
                            if(k<m2.height && l<m2.width && height < m1.height && width <m1.width){
                                convolved.map[i][j] = convolved.map[i][j] + m1.map[height][width]* m2.map[k][l];
                                l++;
                        }
                    }
                    l=0;
                    k++;
                }
            }
        }
    }
    else{
        int step_h = m2.height-1;
        int step_w = m2.width-1;
        for(int i=0; i<m1.height-step_h;i++){
            for(int j =0; j<m1.width-step_w;j++){
                int k =0, l =0;
                for(int height = i; height <=i+step_h ; height++){
                    for(int width = j; width <= j+step_w; width++){
                        if(k<m2.height && l<m2.width && height < m1.height && width <m1.width){
                           convolved.map[i][j] = convolved.map[i][j] + m1.map[height][width]* m2.map[k][l];
                            l++;
                            }
                        }
                        l=0;
                        k++;
                    }
                }
            }
        
    }
    return convolved;
    
}

Image sobel(Image inputImage){
    Matrix matrixImage = image2Matrix(inputImage);
    Matrix Si = createMatrix(3, 3);
    Si.map[0][0] = 1.0;
    Si.map[0][1] = 2.0;
    Si.map[0][2] = 1.0;
    Si.map[1][0] = 0.0;
    Si.map[1][1] = 0.0;
    Si.map[1][2] = 0.0;
    Si.map[2][0] = -1.0;
    Si.map[2][1] = -2.0;
    Si.map[2][2] = -1.0;
    
    Matrix Sj = createMatrix(3, 3);
    Sj.map[0][0] = 1.0;
    Sj.map[0][1] = 0.0;
    Sj.map[0][2] = -1.0;
    Sj.map[1][0] = 2.0;
    Sj.map[1][1] = 0.0;
    Sj.map[1][2] = -2.0;
    Sj.map[2][0] = 1.0;
    Sj.map[2][1] = 0.0;
    Sj.map[2][2] = -1.0;
    
    Matrix Gx = convolve(matrixImage, Si);
    Matrix Gy = convolve(matrixImage, Sj);
    Matrix G = createMatrix(Gx.height, Gx.width);
    
    
    for(int i =0; i< Gx.height; i++){
        for(int j =0; j<Gx.width; j++){
            G.map[i][j] = sqrt( Gx.map[i][j]*Gx.map[i][j] + Gy.map[i][j]*Gy.map[i][j] );
        }
    }
    
    
    int threshold = 55;
    //scale
    G = scale(G, 0.48);
    //threshold
    Image sobel = createImage(G.height, G.width);
    for(int i =0; i< sobel.height; i++){
        for(int j =0; j<sobel.width; j++){
            if(G.map[i][j] > threshold)
                sobel.map[i][j].i = 255;
            else
                sobel.map[i][j].i =0;
        }
    }
    return sobel;
}

Image canny(Image inputImage){
    Image canny = createImage(inputImage.height, inputImage.width);
    Matrix matrixImage = image2Matrix(inputImage);
    Matrix P = createMatrix(2, 2);
    P.map[0][0] = 0.5;
    P.map[0][1] = 0.5;
    P.map[1][0] = -0.5;
    P.map[1][1] = -0.5;
    
    Matrix Q = createMatrix(2, 2);
    Q.map[0][0] = 0.5;
    Q.map[0][1] = -0.5;
    Q.map[1][0] = 0.5;
    Q.map[1][1] = -0.5;
    
    Matrix Pij = convolve(matrixImage, P);
    Matrix Qij = convolve(matrixImage, Q);
    Matrix m = createMatrix(Pij.height, Pij.width);
    Matrix sector = createMatrix(Pij.height, Pij.width);
    
    for(int i =0; i< Pij.height; i++){
        for(int j =0; j<Pij.width; j++){
            m.map[i][j] = sqrt( Pij.map[i][j]*Pij.map[i][j] + Qij.map[i][j]*Qij.map[i][j] );
        }
    }
    
    /*Matrix alpha = createMatrix(Pij.height, Pij.width);
    for(int i =0; i< Pij.height; i++){
        for(int j =0; j<Pij.width; j++){
            alpha.map[i][j] = atan2(Qij.map[i][j], Pij.map[i][j]);
        }
    }
    
    Matrix sector = createMatrix(Pij.height, Pij.width);
    for(int i =0; i< Pij.height; i++){
        for(int j =0; j<Pij.width; j++){
            if((alpha.map[i][j]>337.5 && alpha.map[i][j]<360) ||
               (alpha.map[i][j]>0 && alpha.map[i][j]<22.5) ||
               (alpha.map[i][j]>157.5 && alpha.map[i][j]<202.5))
                
        }
    }*/
    
    for(int i =0; i< m.height; i++){
        for(int j =0; j<m.width; j++){
            sector.map[i][j] = m.map[i][j];
        }
    }
    
    //discussed with Harshit and Yash
    double val = 180.0/M_PI;
    for(int x=1; x<m.height-1; x++){
        for(int y=1; y<m.width-1; y++){
            double arctan = atan2(Qij.map[x][y], Pij.map[x][y]) * val;
            
            if(arctan<0.0)
                arctan = arctan+180;
            
            
            if((arctan>=0 && arctan<=22.5) || (arctan>=155 && arctan<=180)){
                if ((m.map[x][y]<m.map[x][y+1]) || (m.map[x][y]<m.map[x][y-1]))
                    sector.map[x][y] = 0;
            }
            else if(arctan>22.5 && arctan<=67.5){
                if ((m.map[x][y]<m.map[x+1][y+1]) || (m.map[x][y]<m.map[x-1][y-1]))
                    sector.map[x][y] = 0;
            }
            else if(arctan>67.5 && arctan<=112.5){
                if((m.map[x][y]<m.map[x+1][y]) || (m.map[x][y]<m.map[x-1][y]))
                    sector.map[x][y] = 0;
            }
            else{
                if((m.map[x][y]<m.map[x+1][y-1]) || (m.map[x][y]<m.map[x-1][y+1]))
                    sector.map[x][y] = 0;
            }
        }
    }
    //scale
    sector = scale(sector, 0.38);
    
    //threshold for 0, 255 and -1 (candidate)
    double lowThreshold = 30.0;
    double highThreshold = 70.0;
    
    
    for(int x=0; x<sector.height; x++){
        for(int y=0; y<sector.width; y++){
            if(sector.map[x][y]>highThreshold)
                sector.map[x][y] = 255.0;
            else if(sector.map[x][y]<lowThreshold)
                sector.map[x][y] = 0.0;
            else
                sector.map[x][y] = -1.0;
        }
    }
    
    //coordinates neighbours
    int x_cord[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int y_cord[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for(int x=0; x<inputImage.height; x++){
        for(int y=0; y<inputImage.width; y++){
            if(sector.map[x][y] == -1.0){
                for(int i=0; i<8; i++){
                    int x_val = x + x_cord[i];
                    int y_val = y + y_cord[i];
                    if(x_val>=0 && x_val<sector.height && y_val>=0 && y_val<sector.width){
                        if(sector.map[x_val][y_val] == 255.0) {
                            canny.map[x][y].i = 255;
                            break;
                        }
                        else
                            canny.map[x][y].i = 0;
                    }
            }
            }
            else
                canny.map[x][y].i = (int) sector.map[x][y];
        }
    }
    return canny;
}
