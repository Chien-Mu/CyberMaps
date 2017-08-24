#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QDebug>
#include <math.h>
#include "cyberglobal.h"
#include "mapsviewer.h"
#include "multilateration.h"



class dataReader : public QThread
{
    Q_OBJECT
public:
    explicit dataReader(QObject *parent = 0);


    void run();
    bool stop;
    void test();

    void get_datareader(WAP *routers);



private:


    int _time_delay;
    QProcess *proc;
    QByteArray input_msg;
    QString _ip;
    QMutex mutex;

    void rssi2distance(int router_index);
    void string_filter(QString msg, int router_index);

    WAP *wap;
    SSID_ptr ids;
    Antenna *ant;
    RSSI *rssi;
    Launch lau;
    MapsViewer *view;
    unsigned WAP_size;

signals:

public slots:
};

#endif // DATAREADER_H
