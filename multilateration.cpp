#include "multilateration.h"
#include <math.h>
#include <stdio.h>
#define PI 3.14159265359

#include <QDebug>

void referanceNode(const unsigned numberOfDevice, WAP *waps, lastDistance *lastDist)
{

    int i=0;

    waps[0].wapX = 0;
    waps[0].wapY = 0;

    for(i=0; i<(int)(numberOfDevice-1); i++)
    {
        if(waps[1].ant[0].rssis[i].ssid_index==0)
        {
            //waps[1].wapX = waps[1].ant[0].rssis[i].distance;
            waps[1].wapX = lastDist[0].distance;;   //phymon:use ant 1 to cal
            waps[1].wapY = 0;
        }
    }

    qDebug()<< "B.x = " << waps[1].wapX;
    qDebug()<< "B.y = " << waps[1].wapY;


    float alpha=0.0, cosine=0.0;
    /*
    float d01=0.0, d1i=0.0, d2i=0.0;
    for(int i=2; i<numberOfDevice; i++)
    {
        d01 = waps[0].ant[0].rssis[0].distance;
        d1i = waps[0].ant[0].rssis[i-1].distance;
        d2i = waps[1].ant[1].rssis[(numberOfDevice-1)+(i-1)].distance;

        cosine = (d01^2 + d1i^2 - d2i^2)/(2*d01*d1i);
        alpha = acos(cosine);

        waps[i].wapX = d1i*cos(alpha*180/PI);
        waps[i].wapY = d1i*sin(alpha*180/PI);
    }
    */

    float d01=0.0, d02=0.0, d12=0.0;
/*    for(i=0; i<(int)numberOfDevice; i++)
    {
        if(waps[0].ant[0].rssis[i].ssid_index==1)   //B
        {
            d01 = waps[0].ant[0].rssis[i].distance;
        }
        else if(waps[0].ant[0].rssis[i].ssid_index==2)  //C
        {
            d02 = waps[0].ant[0].rssis[i].distance;
        }
    }
*/
    d01 = lastDist[0].distance;
    d02 = lastDist[2].distance;
    d12 = lastDist[1].distance;

    qDebug()<<"d01="<<d01;
    qDebug()<<"d02="<<d02;
    qDebug()<<"d12="<<d12;


/*
    for(i=0; i<(int)numberOfDevice; i++)
    {
        if(waps[1].ant[0].rssis[i].ssid_index==2)
        {
            d12 = waps[1].ant[0].rssis[i].distance;
        }
    }
*/

    cosine = (pow(d01,2) + pow(d02,2) - pow(d12,2))/(2*d01*d02);
    alpha = acos(cosine);

    waps[2].wapX = (float)(d02*cos(alpha));
    waps[2].wapY = (float)(d02*sin(alpha));

    qDebug()<< "C.x = " << waps[2].wapX;
    qDebug()<< "C.y = " << waps[2].wapY;

/*

    if(numberOfDevice>=4)
    {
        float gaussianMatrix[3][4]={{0.0}};

        float A=0.0, B=0.0, C=0.0;
        float di0=0.0, di1=0.0, di2=0.0;

        for(i=3; i<(int)numberOfDevice; i++)
        {
            for(int j=0; j<(int)numberOfDevice; j++)
            {
                if(waps[i].ant[0].rssis[j].ssid_index==0)
                {
                    di0 = waps[i].ant[0].rssis[j].distance;
                }
                else if(waps[i].ant[0].rssis[j].ssid_index==1)
                {
                    di1 = waps[i].ant[0].rssis[j].distance;
                }
                else if(waps[i].ant[0].rssis[j].ssid_index==2)
                {
                    di2 = waps[i].ant[0].rssis[j].distance;
                }
            }

            A = pow(di0,2) - pow(waps[0].wapX,2) - pow(waps[0].wapY,2);
            B = pow(di1,2) - pow(waps[1].wapX,2) - pow(waps[1].wapY,2);
            C = pow(di2,2) - pow(waps[2].wapX,2) - pow(waps[2].wapY,2);

            float matrix[3][4]={{1.0, -2*waps[0].wapX, -2*waps[0].wapY, A},
                                {1.0, -2*waps[1].wapX, -2*waps[1].wapY, B},
                                {1.0, -2*waps[2].wapX, -2*waps[2].wapY, C}};


            gaussianElimination(matrix, gaussianMatrix);

            waps[i].wapY = gaussianMatrix[2][3]/gaussianMatrix[2][2];
            waps[i].wapX = (gaussianMatrix[1][3] - waps[i].wapY*gaussianMatrix[1][2])/gaussianMatrix[1][1];

            qDebug()<< "D.x = " << waps[i].wapY;
            qDebug()<< "D.y = " << waps[i].wapX;
        }
    }

*/

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


/*
void targetNode(const unsigned numberOfDevice, WAP *waps)
{
    ;
}
*/


