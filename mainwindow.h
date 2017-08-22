#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "mapsviewer.h"
#include "cyberglobal.h"
#include "datareader.h"
#include "multilateration.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    dataReader *datareader;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    MapsViewer *view;

    //data struct
    WAP *wap;
    SSID_ptr ids;
    Antenna *ant;
    RSSI *rssi;
    Launch lau;

};

#endif // MAINWINDOW_H
