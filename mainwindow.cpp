#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    const unsigned WAP_size = 4;
    WAP wap[WAP_size];
    char ids[][SSID_SIZE] = {{"Aasdaadsf"},{"Badf"},{"Casdf"},{"Ddddddddddd"}};
    Antenna ant[WAP_size*1];
    //RSSI rssi[WAP_size*2];
    RSSI rssi[12];
    Launch lau;


    wap[0].SSID = &ids[0]; //A
    wap[0].index = 0;
    //wap[0].wapX = 100;
    //wap[0].wapY = 100;
    wap[0].antenna_size = 1;
    //ant[0].antX = 100;
    //ant[0].antY = 100;
    ant[0].rssis_size  = 2;
    rssi[0].SSID = &ids[1]; //B
    rssi[0].SSID_index = 1;
    rssi[0].dBm = 50;
    rssi[0].distance = 80;
    rssi[1].SSID = &ids[2]; //C
    rssi[1].SSID_index = 2;
    rssi[1].dBm = 100;
    rssi[1].distance = 113.137f;
    rssi[2].SSID = &ids[3]; //D
    rssi[2].SSID_index = 3;
    rssi[2].dBm = 100;
    rssi[2].distance = 80;
    ant[0].rssis = rssi;
    lau.dBm = 50;
    lau.distance = 40;
    ant[0].lau = lau;
    wap[0].ant = &ant[0];

    wap[1].SSID = &ids[1];  //B
    wap[1].index = 1;
    //wap[1].wapX = 150;
    //wap[1].wapY = 150;
    wap[1].antenna_size = 1;
    //ant[1].antX = 150;
    //ant[1].antY = 150;
    ant[1].rssis_size  = 2;
    rssi[3].SSID = &ids[0]; //A
    rssi[3].SSID_index = 0;
    rssi[3].dBm = 50;
    rssi[3].distance = 80;
    rssi[4].SSID = &ids[2]; //C
    rssi[4].SSID_index = 2;
    rssi[4].dBm = 50;
    rssi[4].distance = 80;
    rssi[5].SSID = &ids[3]; //D
    rssi[5].SSID_index = 3;
    rssi[5].dBm = 50;
    rssi[5].distance = 113.137f;
    ant[1].rssis = &rssi[3];
    ant[1].lau = lau;
    wap[1].ant = &ant[1];

    wap[2].SSID = &ids[2];  //C
    wap[2].index = 2;
    //wap[2].wapX = 200;
    //wap[2].wapY = 100;
    wap[2].antenna_size = 1;
    //ant[2].antX = 200;
    //ant[2].antY = 100;
    ant[2].rssis_size  = 2;
    rssi[6].SSID = &ids[0]; //A
    rssi[6].SSID_index = 0;
    rssi[6].dBm = 100;
    rssi[6].distance = 113.137f;
    rssi[7].SSID = &ids[1]; //B
    rssi[7].SSID_index = 1;
    rssi[7].dBm = 50;
    rssi[7].distance = 80;
    rssi[8].SSID = &ids[3]; //D
    rssi[8].SSID_index = 3;
    rssi[8].dBm = 50;
    rssi[8].distance = 80;
    ant[2].rssis = &rssi[6];
    ant[2].lau = lau;
    wap[2].ant = &ant[2];

    wap[3].SSID = &ids[3];  //D
    wap[3].index = 3;
    //wap[3].wapX = 200;
    //wap[3].wapY = 100;
    wap[3].antenna_size = 1;
    //ant[3].antX = 200;
    //ant[3].antY = 100;
    ant[3].rssis_size  = 2;
    rssi[9].SSID = &ids[0]; //A
    rssi[9].SSID_index = 0;
    rssi[9].dBm = 100;
    rssi[9].distance = 80;
    rssi[10].SSID = &ids[1]; //B
    rssi[10].SSID_index = 1;
    rssi[10].dBm = 50;
    rssi[10].distance = 113.137f;
    rssi[11].SSID = &ids[2]; //C
    rssi[11].SSID_index = 2;
    rssi[11].dBm = 50;
    rssi[11].distance = 80;
    ant[3].rssis = &rssi[9];
    ant[3].lau = lau;
    wap[3].ant = &ant[3];



    referanceNode(WAP_size, wap);

    /*
for(unsigned i=0;i<WAP_size;i++){
    qDebug() << "SSID:" << *wap[i].SSID[0];
    for(unsigned j=0;j<wap[i].ant[0].rssis_size;j++)
        qDebug() << "RSSI:" << *wap[i].ant[0].rssis[j].SSID << wap[i].ant[0].rssis[j].dBm;
}

*/

//    QString ip = "";
//    int delay = 0;

//    datareader = new dataReader;
//    datareader->get_datareader(wap, ip, delay);
//    datareader->test();
//    datareader->start();


    view = new MapsViewer;
    view->drawWAPs(wap,WAP_size);
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
