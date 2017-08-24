#include "datareader.h"










dataReader::dataReader(QObject *parent) : QThread(parent)
{
    view = new MapsViewer;
    view->show();
}

void dataReader::test()
{
    QString msg = "111";
    //string_filter(msg);

}

void dataReader::get_datareader(WAP *routers)
{
    //wap = routers;
    //qDebug()<<wap[0].ant[0].rssis[0].dBm;
    //qDebug()<<"routers = " << routers;
    //qDebug()<<"wap = " <<wap;
}

void dataReader::rssi2distance(int router_index)
{
    if(router_index == 1)
    {
        float rssi_1 = wap[0].ant[0].rssis[0].dBm;
        float rssi_2 = wap[0].ant[1].rssis[0].dBm;

        float distance_1 = exp((rssi_1+32.851)/(-8.782));
        float distance_2 = exp((rssi_2+28.858)/(-7.27));

        wap[0].ant[0].rssis[0].distance = distance_1;
        wap[0].ant[1].rssis[0].distance = distance_2;
    }

    qDebug()<<"distance1"<< wap[0].ant[0].rssis[0].distance;
    qDebug()<<"distance2"<< wap[0].ant[1].rssis[0].distance;



}

void dataReader::string_filter(QString msg, int router_index)
{
/*
    qDebug()<<"MAC:"<<msg.mid(5,17);
    qDebug()<<"RSSI1"<<(msg.mid(30,3)).toFloat();
    qDebug()<<"RSSI2"<<(msg.mid(34,3)).toFloat();
    qDebug()<<wap[0].ant[0].rssis[0].dBm;       */

    //wap[0].SSID = msg.mid(5,17);

    QStringList msg_list = msg.split("\n");
    WAP_size = (msg_list.length())-1;
    QString str[WAP_size];

    for(int i=0;i<WAP_size;i++)
    {
        QString each_router_msg = msg_list.at(0);
        str[i] = msg_list.at(i).mid(5,17);
        qDebug()<<"str"<<i<<"="<<str[i];
    }



    wap = new WAP[WAP_size];
    ant = new Antenna[WAP_size*2];
    rssi = new RSSI[2*WAP_size*(WAP_size-1)];
    ids = new char[WAP_size][SSID_SIZE]();

    for(unsigned i = 0 ; i < WAP_size ; i++)
        for(int j = 0 ; j < str[i].size() && j < SSID_SIZE ; j++)
            ids[i][j] = str[i].at(j).toLatin1();

    ant[0].rssis = rssi;
    ant[0].lau = lau;
    wap[0].ant = &ant[0];

    for (int i=1;i<=int(WAP_size);i++)
    {
        ant[i].rssis = &rssi[i*3];
        wap[i].ant = &ant[i];
        ant[i].lau = lau;
    }



    /*
    ant[1].rssis = &rssi[3];
    wap[1].ant = &ant[1];


    ant[2].rssis = &rssi[6];
    wap[2].ant = &ant[2];
    ant[3].rssis = &rssi[9];
    wap[3].ant = &ant[3];     */


    for(int i=0;i<WAP_size;i++)
    {
        qDebug()<<"i = " << i;

        wap[i].ant[0].rssis[0].dBm = (msg_list.at(i).mid(30,3)).toFloat();
        wap[i].ant[1].rssis[0].dBm = (msg_list.at(i).mid(34,3)).toFloat();

    }






    qDebug()<<"rssi1_string fil"<< wap[0].ant[0].rssis[0].dBm;
    qDebug()<<"rssi2_string fil"<< wap[0].ant[1].rssis[0].dBm;

    //qDebug()<<

}



void dataReader::run()
{
    QString ip = "10.10.10.101";
    int time_delay = 1000;
 /*
    const unsigned WAP_size = 4;
    wap = new WAP[WAP_size];
    ant = new Antenna[WAP_size*1];
    rssi = new RSSI[12];

    ids = new char[WAP_size][SSID_SIZE]();
    QString str[WAP_size];
    str[0] = "Aasdaadsf";
    str[1] = "Badf";
    str[2] = "Casdfsdaf";
    str[3] = "Dddddddd";
    for(unsigned i = 0 ; i < WAP_size ; i++)
        for(int j = 0 ; j < str[i].size() && j < SSID_SIZE ; j++)
            ids[i][j] = str[i].at(j).toLatin1();


    ant[0].rssis = rssi;
    wap[0].ant = &ant[0];
    ant[1].rssis = &rssi[3];
    wap[1].ant = &ant[1];
    ant[2].rssis = &rssi[6];
    wap[2].ant = &ant[2];
    ant[3].rssis = &rssi[9];
    wap[3].ant = &ant[3];
    */

    /*
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
    ant[1].rssis_size  = 3;
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
    ant[2].rssis_size  = 3;
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
    ant[3].rssis_size  = 3;
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
*/

    this->get_datareader(wap);


    while(1)
    {
        proc = new QProcess;
        proc->start("curl http://10.10.10.254/cgi-bin/stainfo.cgi -u admin:admin");
        //proc->start("ifconfig");
        this->msleep(time_delay);
        if (!proc->waitForStarted())
        {
            qDebug()<<"start fail";
        }

        while(proc->waitForFinished())
        {
            ;
        }

        QString input_msg = proc->readAll().data();
        qDebug()<<"input_msg:"<<input_msg;
        //qDebug()<<"split test 1 "<<router1;
        QStringList msg_list = input_msg.split("\n");
        qDebug()<<"msg list=" << msg_list;
        qDebug()<<"msg list len"<< msg_list.length();
        this->string_filter(QString(input_msg), 1);
        this->rssi2distance(1);
        referanceNode(WAP_size, wap);
        view->drawWAPs(wap,WAP_size);
        delete wap;
        delete rssi;
        delete ant;

    }
}
