#include "datareader.h"

dataReader::dataReader(QObject *parent) : QThread(parent)
{

}

void dataReader::test()
{
    QString msg = "111";
    string_filter(msg);

}

void dataReader::get_datareader(WAP *routers,
                                QString ip,
                                int time_delay)
{
    _routers = routers;
    _time_delay = time_delay;
    _ip = ip;

    qDebug()<<"routers = " << routers;
    qDebug()<<"_routers = " <<_routers;
}

void dataReader::rssi2distance()
{


}

void dataReader::string_filter(QString msg)
{
    mutex.lock();
    _routers[0].SSID = &_ssid_router[0];
    _routers[0].index = 123123;
    _routers[0].antenna_size = 1;
    mutex.unlock();

    //qDebug()<<

}



void dataReader::run()
{



    while(1)
    {
        proc = new QProcess;
        proc->start("http://10.10.10.254");
        if (!proc->waitForStarted())
        {
            qDebug()<<"start fail";
        }
/*
        while(proc->waitForFinished())
        {
            ;
        }
*/
        input_msg = proc->readAll().data();
        string_filter(QString(input_msg));
        rssi2distance();
        this->msleep(_time_delay);
    }
}
