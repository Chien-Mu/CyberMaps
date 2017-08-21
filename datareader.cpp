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
    qDebug()<<_routers[0].ant[0].rssis[0].dBm;
    qDebug()<<"routers = " << routers;
    qDebug()<<"_routers = " <<_routers;
}

void dataReader::rssi2distance()
{


}

void dataReader::string_filter(QString msg)
{
    mutex.lock();
    qDebug()<<"MAC:"<<msg.mid(5,17);
    qDebug()<<"RSSI1"<<(msg.mid(30,3)).toFloat();
    qDebug()<<"RSSI2"<<(msg.mid(34,3)).toFloat();
    qDebug()<<_routers[0].ant[0].rssis[0].dBm;

//    _routers[0].SSID = msg.mid(5,17);
//    _routers[0].ant[0].rssis[0].dBm = (msg.mid(30,3)).toFloat();
//    _routers[0].ant[0].rssis[0].dBm = -23;
//    _routers[0].ant[1].rssis->dBm = (msg.mid(34,3)).toFloat();

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
        proc->start("curl http://10.10.10.254/cgi-bin/stainfo.cgi -u admin:admin");
        //proc->start("ifconfig");
        this->msleep(_time_delay);
        if (!proc->waitForStarted())
        {
            qDebug()<<"start fail";
        }

        while(proc->waitForFinished())
        {
            ;
        }

        input_msg = proc->readAll().data();
        qDebug()<<"input_msg:"<<input_msg;
        string_filter(QString(input_msg));
        rssi2distance();

    }
}
