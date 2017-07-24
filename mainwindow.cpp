#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new MapsViewer;

    QVector<WAP> waps;
    QVector<RSSI> rssis;
    WAP wap;
    RSSI rssi;

    rssi.SSID = 'A';
    rssi.SS = 100;
    rssis.push_back(rssi);
    rssi.SSID = 'B';
    rssi.SS = 200;
    rssis.push_back(rssi);
    rssi.SSID = 'C';
    rssi.SS = 300;
    rssis.push_back(rssi);

    wap.SSID = 'A';
    wap.location = QPoint(100,100);
    wap.RSSIs.push_back(rssis[1]);
    wap.RSSIs.push_back(rssis[2]);
    waps.push_back(wap);

    wap.SSID = 'B';
    wap.location = QPoint(100,200);
    wap.RSSIs.push_back(rssis[0]);
    wap.RSSIs.push_back(rssis[2]);
    waps.push_back(wap);

    wap.SSID = 'C';
    wap.location = QPoint(20,300);
    wap.RSSIs.push_back(rssis[0]);
    wap.RSSIs.push_back(rssis[1]);
    waps.push_back(wap);


    view->drawWAPs(waps);
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
