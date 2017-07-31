#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    const unsigned WAP_size = 3;
    WAP wap[WAP_size];
    char ids[][SSID_SIZE] = {{"Aasdaadsf"},{"Badf"},{"Casdf"}};
    Antenna ant[WAP_size*1];
    RSSI rssi[WAP_size*2];
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
    lau.dBm = 50;
    lau.distance = 40;
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


    /*
for(unsigned i=0;i<WAP_size;i++){
    qDebug() << "SSID:" << *wap[i].SSID[0];
    for(unsigned j=0;j<wap[i].ant[0].rssis_size;j++)
        qDebug() << "RSSI:" << *wap[i].ant[0].rssis[j].SSID << wap[i].ant[0].rssis[j].dBm;
}

*/

    QString ip = "";
    int delay = 0;

    datareader = new dataReader;
    datareader->get_datareader(wap, ip, delay);
    datareader->test();
    datareader->start();


    view = new MapsViewer;
    //view->drawWAPs(wap,WAP_size);
    //view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
