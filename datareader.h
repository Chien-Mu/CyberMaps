#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QDebug>
#include "cyberglobal.h"


class dataReader : public QThread
{
    Q_OBJECT
public:
    explicit dataReader(QObject *parent = 0);


    void run();
    bool stop;
    void test();

    void get_datareader(WAP *routers,
                        QString ip,
                        int time_delay);



private:
    WAP *_routers;
    SSID_ptr _ssid_router;
    Antenna *_ant_router;
    RSSI *_rssi_router;
    int _time_delay;
    QProcess *proc;
    QByteArray input_msg;
    QString _ip;
    QMutex mutex;

    void rssi2distance();
    void string_filter(QString msg);

signals:

public slots:
};

#endif // DATAREADER_H
