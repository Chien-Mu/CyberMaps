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

    wap.SSID = 'A';
    wap.location = QPoint(100,100);
    rssi.SSID = 'B';
    rssi.SS = 50;
    wap.RSSIs.push_back(rssi);
    rssi.SSID = 'C';
    rssi.SS = 100;
    wap.RSSIs.push_back(rssi);
    waps.push_back(wap);

    wap.SSID = 'B';
    wap.location = QPoint(150,150);
    rssi.SSID = 'A';
    rssi.SS = 50;
    wap.RSSIs[0] = rssi;
    rssi.SSID = 'C';
    rssi.SS = 50;
    wap.RSSIs[1] = rssi;
    waps.push_back(wap);

    wap.SSID = 'C';
    wap.location = QPoint(200,100);
    rssi.SSID = 'A';
    rssi.SS = 100;
    wap.RSSIs[0] = rssi;
    rssi.SSID = 'B';
    rssi.SS = 50;
    wap.RSSIs[1] = rssi;
    waps.push_back(wap);

    view->drawWAPs(waps);
    view->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
