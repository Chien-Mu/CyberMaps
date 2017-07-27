#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

//dst 空間要與 src 一樣
void cloneWAP(WAP *src, unsigned src_size,
              WAP *dst, SSID_ptr dst_ssid, Antenna *dst_ant, RSSI *dst_rssi){

    int jj=0,kk=0;
    for(unsigned i=0;i<src_size;i++){
        dst[i] = src[i];
        dst[i].SSID = &dst_ssid[i];
        //ssid by value
        for(unsigned ii=0;src[i].SSID[0][ii] != '\0';ii++)
            dst_ssid[i][ii] = src[i].SSID[0][ii];

        dst[i].ant = &dst_ant[jj]; //by address, jj 0 2 4
        for(unsigned j=0;j<src[i].antenna_size;j++){
            dst_ant[jj++] = src[i].ant[j]; //by value, jj 0123456,j 01 01 01
            dst[i].ant[j].rssis = &dst_rssi[kk];
            for(unsigned k=0;k<src[i].ant[j].rssis_size;k++){
                dst_rssi[kk++] = src[i].ant[j].rssis[k];
                dst[i].ant[j].rssis[k].SSID = &dst_ssid[ src[i].ant[j].rssis[k].SSID_index ];
            }
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const unsigned WAP_size = 3;
    WAP wap[WAP_size];
    char ids[][SSID_SIZE] = {{"A"},{"B"},{"C"}};
    Antenna ant[3];
    RSSI rssi[2*3];
    Launch lau;

    wap[0].SSID = &ids[0]; //A
    wap[0].index = 0;
    wap[0].wapX = 100;
    wap[0].wapY = 100;
    wap[0].antenna_size = 1;
    ant[0].antX = 100;
    ant[0].antY = 100;
    ant[0].rssis_size  = 2;
    rssi[0].SSID = &ids[1]; //B
    rssi[0].SSID_index = 1;
    rssi[0].dBm = 50;
    rssi[0].distance = 40;
    rssi[1].SSID = &ids[2]; //C
    rssi[1].SSID_index = 2;
    rssi[1].dBm = 100;
    rssi[1].distance = 90;
    ant[0].rssis = rssi;
    lau.dBm = 200;
    lau.distance = 190;
    ant[0].lau = lau;
    wap[0].ant = ant;

    wap[1].SSID = &ids[1];
    wap[1].index = 1;
    wap[1].wapX = 150;
    wap[1].wapY = 150;
    wap[1].antenna_size = 1;
    ant[1].antX = 150;
    ant[1].antY = 150;
    ant[1].rssis_size  = 2;
    rssi[2].SSID = &ids[0];
    rssi[2].SSID_index = 0;
    rssi[2].dBm = 50;
    rssi[2].distance = 40;
    rssi[3].SSID = &ids[2];
    rssi[3].SSID_index = 2;
    rssi[3].dBm = 50;
    rssi[3].distance = 40;
    ant[1].rssis = &rssi[2];
    lau.dBm = 250;
    ant[1].lau = lau;
    wap[1].ant = &ant[1];

    wap[2].SSID = &ids[2];
    wap[2].index = 2;
    wap[2].wapX = 200;
    wap[2].wapY = 100;
    wap[2].antenna_size = 1;
    ant[2].antX = 200;
    ant[2].antY = 100;
    ant[2].rssis_size  = 2;
    rssi[4].SSID = &ids[0];
    rssi[4].SSID_index = 0;
    rssi[4].dBm = 100;
    rssi[4].distance = 90;
    rssi[5].SSID = &ids[1];
    rssi[5].SSID_index = 1;
    rssi[5].dBm = 50;
    rssi[5].distance = 40;
    ant[2].rssis = &rssi[4];
    ant[2].lau = lau;
    wap[2].ant = &ant[2];

    for(unsigned i=0;i<WAP_size;i++){
        qDebug() << "SSID:" << *wap[i].SSID;
        for(unsigned j=0;j<wap[i].ant[0].rssis_size;j++)
            qDebug() << "RSSI:" << *wap[i].ant[0].rssis[j].SSID << wap[i].ant[0].rssis[j].dBm;
    }
    qDebug() << "----------------------";

    WAP wap2[WAP_size];
    char ids2[3][SSID_SIZE];
    Antenna ant2[3];
    RSSI rssi2[2*3];
    cloneWAP(wap,WAP_size,wap2,ids2,ant2,rssi2);
    ant2[0].antX = 1000;
    rssi2[5].dBm = 1234;
    ids2[1][1] = 'F';
    for(unsigned i=0;i<WAP_size;i++){
        qDebug() << "SSID:" << *wap2[i].SSID;
        qDebug() << "WAPX:" << wap2[i].wapX << "WAPY:" << wap2[i].wapY;
        qDebug() << "ant:" << wap2[i].ant[0].antX << wap2[i].ant[0].antY;
        qDebug() << "lau" << wap2[i].ant[0].lau.dBm;
        for(unsigned j=0;j<wap2[i].ant[0].rssis_size;j++){
            qDebug() << "RSSI:" << *wap2[i].ant[0].rssis[j].SSID << wap2[i].ant[0].rssis[j].dBm;
        }
    }

    //view = new MapsViewer;
    //view->drawWAPs(wap);
    //view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
