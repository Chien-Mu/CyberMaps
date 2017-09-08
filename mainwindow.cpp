#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    datareader = new dataReader;

/*
    const unsigned wap_size = 4;
    wap = new WAP[wap_size];
    ant = new Antenna[wap_size*1];
    rssi = new RSSI[12];
    dist = new Distance[12];

    ids = new char *[wap_size];
    for(unsigned i=0 ; i<wap_size ; i++)
        ids[i] = new char[SSID_SIZE]();
    QString str[wap_size];
    str[0] = "Aasdaadsf";
    str[1] = "Badf";
    str[2] = "Casdfsdaf";
    str[3] = "Dddddddd";
    for(unsigned i = 0 ; i < wap_size ; i++)
        for(int j = 0 ; j < str[i].size() && j < SSID_SIZE ; j++)
            ids[i][j] = str[i].at(j).toLatin1();


    wap[0].ssid = ids[0]; //A
    wap[0].index = 0;
    wap[0].wapX = 0.0;
    wap[0].wapY = 0.0;
    wap[0].dist_size = 3;
    dist[0].ssid = ids[1]; //B
    dist[0].ssid_index = 1;
    dist[0].distance = 80;
    dist[1].ssid = ids[2]; //C
    dist[1].ssid_index = 2;
    dist[1].distance = 113.137f;
    dist[2].ssid = ids[3]; //D
    dist[2].ssid_index = 3;
    dist[2].distance = 80;
    wap[0].dist = dist;
    wap[0].antenna_size = 1;
    ant[0].antX = 0.0;
    ant[0].antY = 0.0;
    ant[0].rssis_size  = 3;
    rssi[0].ssid = ids[1]; //B
    rssi[0].ssid_index = 1;
    rssi[0].dBm = 50;
    rssi[1].ssid = ids[2]; //C
    rssi[1].ssid_index = 2;
    rssi[1].dBm = 100;
    rssi[2].ssid = ids[3]; //D
    rssi[2].ssid_index = 3;
    rssi[2].dBm = 100;
    ant[0].rssis = rssi;
    lau.dBm = 50;
    ant[0].lau = lau;
    wap[0].ant = &ant[0];

    wap[1].ssid = ids[1];  //B
    wap[1].index = 1;
    wap[1].wapX = 80.0;
    wap[1].wapY = 0.0;
    wap[1].dist_size = 3;
    dist[3].ssid = ids[0]; //A
    dist[3].ssid_index = 0;
    dist[3].distance = 80;
    dist[4].ssid = ids[2]; //C
    dist[4].ssid_index = 2;
    dist[4].distance = 80;
    dist[5].ssid = ids[3]; //D
    dist[5].ssid_index = 3;
    dist[5].distance = 113.137f;
    wap[1].dist = &dist[3];
    wap[1].antenna_size = 1;
    ant[1].antX = 0.0;
    ant[1].antY = 0.0;
    ant[1].rssis_size  = 3;
    rssi[3].ssid = ids[0]; //A
    rssi[3].ssid_index = 0;
    rssi[3].dBm = 50;
    rssi[4].ssid = ids[2]; //C
    rssi[4].ssid_index = 2;
    rssi[4].dBm = 50;
    rssi[5].ssid = ids[3]; //D
    rssi[5].ssid_index = 3;
    rssi[5].dBm = 50;
    ant[1].rssis = &rssi[3];
    ant[1].lau = lau;
    wap[1].ant = &ant[1];

    wap[2].ssid = ids[2];  //C
    wap[2].index = 2;
    wap[2].wapX = 80.0;
    wap[2].wapY = 80.0;
    wap[2].dist_size = 3;
    dist[6].ssid = ids[0]; //A
    dist[6].ssid_index = 0;
    dist[6].distance = 113.137f;
    dist[7].ssid = ids[1]; //B
    dist[7].ssid_index = 1;
    dist[7].distance = 80;
    dist[8].ssid = ids[3]; //D
    dist[8].ssid_index = 3;
    dist[8].distance = 80;
    wap[2].dist = &dist[6];
    wap[2].antenna_size = 1;
    ant[2].antY = 0.0;
    ant[2].antX = 0.0;
    ant[2].rssis_size  = 3;
    rssi[6].ssid = ids[0]; //A
    rssi[6].ssid_index = 0;
    rssi[6].dBm = 100;
    rssi[7].ssid = ids[1]; //B
    rssi[7].ssid_index = 1;
    rssi[7].dBm = 50;
    rssi[8].ssid = ids[3]; //D
    rssi[8].ssid_index = 3;
    rssi[8].dBm = 50;
    ant[2].rssis = &rssi[6];
    ant[2].lau = lau;
    wap[2].ant = &ant[2];

    wap[3].ssid = ids[3];  //D
    wap[3].index = 3;
    wap[3].wapX = 0.0;
    wap[3].wapY = 80.0;
    wap[3].dist_size = 3;
    dist[9].ssid = ids[0]; //A
    dist[9].ssid_index = 0;
    dist[9].distance = 80;
    dist[10].ssid = ids[1]; //B
    dist[10].ssid_index = 1;
    dist[10].distance = 113.137f;
    dist[11].ssid = ids[2]; //C
    dist[11].ssid_index = 2;
    dist[11].distance = 80;
    wap[3].dist = &dist[9];
    wap[3].antenna_size = 1;
    ant[3].antX = 0.0;
    ant[3].antY = 0.0;
    ant[3].rssis_size  = 3;
    rssi[9].ssid = ids[0]; //A
    rssi[9].ssid_index = 0;
    rssi[9].dBm = 100;
    rssi[10].ssid = ids[1]; //B
    rssi[10].ssid_index = 1;
    rssi[10].dBm = 50;
    rssi[11].ssid = ids[2]; //C
    rssi[11].ssid_index = 2;
    rssi[11].dBm = 50;
    ant[3].rssis = &rssi[9];
    ant[3].lau = lau;
    wap[3].ant = &ant[3];

    //referanceNode(wap_size, wap);

    //存入最後計算結果
    const unsigned lastDist_size = 3;
    lastDistance lastDist[lastDist_size];
    lastDist[0].distance = 80;
    lastDist[0].index1 = 0;
    lastDist[0].index2 = 1;
    lastDist[1].distance = 80;
    lastDist[0].index1 = 0;
    lastDist[0].index2 = 1;
    lastDist[2].distance = 113.137f;
    lastDist[2].index1 = 2;
    lastDist[2].index2 = 0;

    view = new MapsViewer;
    view->show();
    view->drawWAPs(wap, wap_size, lastDist, lastDist_size);
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->datareader->start();
}
