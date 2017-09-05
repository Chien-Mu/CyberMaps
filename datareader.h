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
    void stop();
    bool isStop;
    void test();

private:
    int _time_delay;
    QProcess *proc;
    QByteArray input_msg;
    QString _ip;
    QMutex mutex;

    void site_survery_filter(QString msg, QString device_mac);
    void rssi2distance(int router_index);
    void inputArrayMap(QString linkHostMAC, QString &value, bool isServer = false);
    void clearArray(int size);

    WAP *wap;
    SSID_arr ids;
    char id_NULL[4];
    Antenna *ant;
    RSSI *rssi;
    MapsViewer *view;
    unsigned wap_size;
    unsigned ant_size;
    unsigned rssi_size;
    unsigned oarn;

signals:

public slots:
};

#endif // DATAREADER_H
