#include "datareader.h"
#include <iostream>
using namespace std;

dataReader::dataReader(QObject *parent) : QThread(parent)
{
    this->isStop = false;
    id_NULL[0] = 'N';
    id_NULL[1] = 'U';
    id_NULL[2] = 'L';
    id_NULL[3] = 'L';
    wap = 0;
    ant = 0;
    rssi = 0;
    ids = 0;

    view = new MapsViewer;
    view->show();
}

void dataReader::test()
{
    QString msg = "111";
    //string_filter(msg);

}

void dataReader::site_survery_filter(QString msg, QString device_mac)
{
    QStringList site_survery_list = msg.split("\n");
    int router_count = site_survery_list.size();
    for(int i=0; i<=router_count; i++)
    {
        QStringList list = site_survery_list[i].split(":");
        //qDebug()<<"router list"<<site_survery_list[i];
        if(site_survery_list[i].size() > 0 && list.size()>1 && list[5].mid(0,2) == device_mac)
        {
            QStringList rssi_fil = list[5].split("-");
            if (rssi_fil.size()>1)
            {
                qDebug()<<"rssi"<<rssi_fil[1].mid(0,2);
                float rssi = 0-(rssi_fil[1].mid(0,2)).toFloat();
                qDebug()<<"rssi_float"<< rssi;
                wap[1].ant[0].rssis[0].dBm = rssi;
            }
            break;
        }

    }

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



    if(router_index == 2)
    {

        float rssi_1 = wap[0].ant[0].rssis[1].dBm;
        float rssi_2 = wap[0].ant[1].rssis[1].dBm;

        float distance_1 = exp((rssi_1+32.851)/(-8.782));
        float distance_2 = exp((rssi_2+28.858)/(-7.27));

        wap[0].ant[0].rssis[1].distance = distance_1;
        wap[0].ant[1].rssis[1].distance = distance_2;
    }

    qDebug()<<"distance1"<< wap[0].ant[0].rssis[1].distance;
    qDebug()<<"distance2"<< wap[0].ant[1].rssis[1].distance;

    if(router_index == 3)
    {

        float rssi_1 = wap[1].ant[0].rssis[0].dBm;


        float distance_1 = exp((rssi_1+32.851)/(-8.782));


        wap[1].ant[0].rssis[0].distance = distance_1;

    }

    qDebug()<<"distance1"<< wap[0].ant[0].rssis[1].distance;



}



void dataReader::stop(){
    isStop = true;
}

void dataReader::run()
{
    isStop = false; //default
    QString ip = "10.10.10.101";
    int time_delay = 1000;



    while(!isStop)
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

        proc->start("curl http://10.10.10.1/cgi-bin/apsurvey.cgi -u admin:admin");
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
        QString input_msg_2 = proc->readAll().data();



        //QString input_msg = proc->readAll().data();
        QString linkHostMAC = "00:66:66:66:66:66";   //levy
        inputArrayMap(linkHostMAC, input_msg, true);  //levy
        site_survery_filter(input_msg_2, "20");
        rssi2distance(1);
        rssi2distance(2);
        rssi2distance(3);
        qDebug()<<"input_msg:"<<input_msg;
        //qDebug()<<"split test 1 "<<router1;
        QStringList msg_list = input_msg.split("\n");
        qDebug()<<"msg list=" << msg_list;
        qDebug()<< msg_list[1];
        qDebug()<<"msg list len"<< msg_list.length() << msg_list.size();
        //this->string_filter(QString(input_msg), 1);
        //this->rssi2distance(1);
        referanceNode(wap_size, wap);
        view->drawWAPs(wap,wap_size);

    }
}

void dataReader::inputArrayMap(QString linkHostMAC ,QString &value, bool isServer){
    //string split
    QStringList list = value.split("\n");

    //固定 78 在 wap[1], 20 在 wap[2]
    if(list.size() >= 3)
        if(list[0].mid(20,2) != "78" && list[1].mid(20,2) == "78"){
            QString tmp = list[1];
            list[1] = list[0];
            list[0] = tmp;
        }

    //create and link memory
    if(isServer){
        //delete
        clearArray(wap_size);

        //create
        wap_size = list.size(); //原應該要 +1(包含link本機也要算進去)，但 split string 都會多切一個空 array，所以就不用
        ant_size = wap_size * DEVICE_ANT;
        oarn = wap_size-1; //One Ant Rssi Number 是每支天線(ant)會得到的RSSI數量
        rssi_size = wap_size * oarn * DEVICE_ANT;
        wap = new WAP[wap_size];
        ant = new Antenna[ant_size];
        rssi = new RSSI[rssi_size];
        ids = new char *[wap_size];
        for(unsigned i=0 ; i<wap_size ; i++)
            ids[i] = new char[SSID_SIZE]();

        //input SSID array
        for(unsigned i = 0 ; i < wap_size ; i++){
            if(i == 0)      //linkHostMAC SSID
                for(int k=0 ; k<linkHostMAC.size() ; k++)
                    ids[0][k] = linkHostMAC[k].toLatin1();
            else{
                QString s = list[i-1].mid(5,17);
                for(int j = 0 ; j < s.size() && j < SSID_SIZE ; j++)
                    ids[i][j] = s[j].toLatin1();
            }
        }

        //link memory and default value
        int antCount=0,rssiCount=0;
        Launch lau;
        lau.dBm = 0.0;
        lau.distance = 0.0;
        for(unsigned i=0 ; i<wap_size ; i++){
            wap[i].index = i;
            wap[i].ssid = ids[i];
            wap[i].wapX = 0.0;
            wap[i].wapY = 0.0;
            wap[i].antenna_size = DEVICE_ANT;
            wap[i].ant = &ant[antCount];
            antCount += DEVICE_ANT;
            for(unsigned j=0 ; j<DEVICE_ANT ; j++){
                wap[i].ant[j].antX = 0.0;
                wap[i].ant[j].antY = 0.0;
                wap[i].ant[j].lau = lau;
                wap[i].ant[j].rssis_size = oarn;
                wap[i].ant[j].rssis = &rssi[rssiCount];
                rssiCount += oarn;
                for(unsigned k=0 ; k<oarn ; k++){
                    wap[i].ant[j].rssis[k].dBm = 0.0;
                    wap[i].ant[j].rssis[k].distance = 0.0;
                    wap[i].ant[j].rssis[k].ssid = id_NULL;
                    wap[i].ant[j].rssis[k].ssid_index = 0;
                }
            }
        }
    }


    int one,sem,two; //semicolon分號
    for(unsigned i=0 ; i<wap_size ; i++)
        if(linkHostMAC == wap[i].ssid){   //只往 linkHostMAC 灌 rssi
            for(unsigned j=0 ; j<oarn ; j++){
                //dBm
                one = list[j].indexOf('-',29);
                sem = list[j].indexOf('/',one);
                two = list[j].indexOf('-',sem);
                rssi[ i * (oarn * DEVICE_ANT) + j ].dBm = list[j].mid(one, sem-one).toFloat();
                rssi[ i * (oarn * DEVICE_ANT) + (j+oarn) ].dBm = list[j].right(list[j].size() - two).toFloat();

                //ssid and ssid_index
                for(unsigned k=0 ; k<wap_size ; k++)
                    if(list[j].mid(5,17) == wap[k].ssid){
                        //A天線
                        rssi[ i * (oarn * DEVICE_ANT) + j ].ssid = wap[k].ssid;
                        rssi[ i * (oarn * DEVICE_ANT) + j ].ssid_index = wap[k].index;
                        //B天線
                        rssi[ i * (oarn * DEVICE_ANT) + (j+oarn) ].ssid = wap[k].ssid;
                        rssi[ i * (oarn * DEVICE_ANT) + (j+oarn) ].ssid_index = wap[k].index;
                        break;
                    }
            }
            break;
        }


    //驗證(test)
    for(unsigned i=0 ; i<wap_size ; i++){
        cout << wap[i].index << endl;
        cout << wap[i].ssid << endl;
        cout << wap[i].antenna_size << endl;
        for(unsigned j=0 ; j<DEVICE_ANT ; j++){
            cout << wap[i].ant[j].rssis_size << endl;
            for(unsigned k=0 ; k<oarn ; k++){
                cout << wap[i].ant[j].rssis[k].ssid << endl;
                cout << wap[i].ant[j].rssis[k].ssid_index << endl;
                cout << wap[i].ant[j].rssis[k].dBm << endl;
                cout << wap[i].ant[j].rssis[k].distance << endl;
            }
        }
    }
}

void dataReader::clearArray(int size){
    if(wap != 0)
        delete[] wap;
    if(ant != 0)
        delete[] ant;
    if(rssi != 0)
        delete[] rssi;
    if(ids != 0){
        for(int i=0;i<size;i++)
            delete[] ids[i];
        delete[] ids;
    }
    wap = 0;
    ant = 0;
    rssi = 0;
    ids = 0;
}
