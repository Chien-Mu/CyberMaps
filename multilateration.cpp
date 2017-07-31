#include "multilateration.h"
#include <math.h>
#include <stdio.h>
#define PI 3.14159265359


void referanceNode(const unsigned numberOfDevice, WAP *waps)
{
    waps[0].wapX = 0;
    waps[0].wapY = 0;

    waps[1].wapX = waps[1].ant[1].rssis[numberOfDevice-1].distance;
    waps[1].wapY = 0;

    float alpha=0.0, cosine=0.0;
    /*
    float d12=0.0, d1i=0.0, d2i=0.0;
    for(int i=2; i<numberOfDevice; i++)
    {
        d12 = waps[0].ant[0].rssis[0].distance;
        d1i = waps[0].ant[0].rssis[i-1].distance;
        d2i = waps[1].ant[1].rssis[(numberOfDevice-1)+(i-1)].distance;

        cosine = (d12^2 + d1i^2 - d2i^2)/(2*d12*d1i);
        alpha = acos(cosine);

        waps[i].wapX = d1i*cos(alpha*180/PI);
        waps[i].wapY = d1i*sin(alpha*180/PI);
    }
    */
    float d12=0.0, d13=0.0, d23=0.0;
    d12 = waps[0].ant[0].rssis[0].distance;
    d13 = waps[0].ant[0].rssis[1].distance;
    d23 = waps[1].ant[1].rssis[(numberOfDevice-1)+1].distance;

    cosine = (pow(d12,2) + pow(d13,2) - pow(d23,2))/(2*d12*d13);
    alpha = acos(cosine);

    waps[2].wapX = (float)(d13*cos(alpha*180/PI));
    waps[2].wapY = (float)(d13*sin(alpha*180/PI));



    if(numberOfDevice>=4)
    {
        float gaussianMatrix[3][4]={0.0f};

        float A=0.0, B=0.0, C=0.0;
        for(int i=3; i<(int)numberOfDevice; i++)
        {
            A = pow(waps[i].ant[i].rssis[(numberOfDevice-1)*i].distance,2) - pow(waps[0].wapX,2) - pow(waps[0].wapY,2);
            B = pow(waps[i].ant[i].rssis[(numberOfDevice-1)*i+1].distance,2) - pow(waps[1].wapX,2) - pow(waps[1].wapY,2);
            C = pow(waps[i].ant[i].rssis[(numberOfDevice-1)*i+2].distance,2) - pow(waps[2].wapX,2) - pow(waps[2].wapY,2);

            float matrix[3][4]={{1.0, -2*waps[0].wapX, -2*waps[0].wapY, A},
                                {1.0, -2*waps[1].wapX, -2*waps[1].wapY, B},
                                {1.0, -2*waps[2].wapX, -2*waps[2].wapY, C}};


            gaussianElimination(matrix, gaussianMatrix);

            waps[i].wapY = gaussianMatrix[2][3]/gaussianMatrix[2][2];
            waps[i].wapX = (gaussianMatrix[1][3] - waps[i].wapY*gaussianMatrix[1][2])/gaussianMatrix[1][1];

        }
    }

}


void gaussianElimination(float matrix[][4], float gaussianMatrix[][4])
{
    int column=0, row=0, index=0;
    float ratio=0.0;

    for(row=0; row<3; row++){
        for(column=0; column<4; column++){

            gaussianMatrix[row][column] = matrix[row][column];

        }
    }


    //upper triangular matrix
    for(column=0; column<3; column++){
        for(row=0; row<3; row++)
        {
            if(row > column)
            {
                ratio = gaussianMatrix[row][column]/gaussianMatrix[column][column];

                for(index=0; index<4; index++){
                    gaussianMatrix[row][index] = gaussianMatrix[row][index] - ratio*gaussianMatrix[column][index];
                }
            }
        }
    }

}


void targetNode(const unsigned numberOfDevice, WAP *waps)
{
    ;
}



