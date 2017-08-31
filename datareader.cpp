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

//    QStringList msg_list = msg.split("\n");
//    wap_size = (msg_list.length())-1;
//    QString str[wap_size];

//    for(int i=0;i<wap_size;i++)
//    {
//        QString each_router_msg = msg_list.at(0);
//        str[i] = msg_list.at(i).mid(5,17);
//        qDebug()<<"str"<<i<<"="<<str[i];
//    }


/*
    wap = new WAP[wap_size];
    ant = new Antenna[wap_size*2];
    rssi = new RSSI[2*wap_size*(wap_size-1)];
    ids = new char[wap_size][SSID_SIZE]();

    for(unsigned i = 0 ; i < wap_size ; i++)
        for(int j = 0 ; j < str[i].size() && j < SSID_SIZE ; j++)
            ids[i][j] = str[i].at(j).toLatin1();

    ant[0].rssis = rssi;
    ant[0].lau = lau;
    wap[0].ant = &ant[0];

    for (int i=1;i<=int(wap_size);i++)
    {
        ant[i].rssis = &rssi[i*3];
        wap[i].ant = &ant[i];
        ant[i].lau = lau;
    }



    for(int i=0;i<wap_size;i++)
    {
        qDebug()<<"i = " << i;

        wap[i].ant[0].rssis[0].dBm = (msg_list.at(i).mid(30,3)).toFloat();
        wap[i].ant[1].rssis[0].dBm = (msg_list.at(i).mid(34,3)).toFloat();

    }






    qDebug()<<"rssi1_string fil"<< wap[0].ant[0].rssis[0].dBm;
    qDebug()<<"rssi2_string fil"<< wap[0].ant[1].rssis[0].dBm;

    //qDebug()<<
*/
}

void dataReader::stop(){
    isStop = true;
}

void dataReader::run()
{
    isStop = false; //default
    QString ip = "10.10.10.101";
    int time_delay = 1000;
 /*
    const unsigned wap_size = 4;
    wap = new WAP[wap_size];
    ant = new Antenna[wap_size*1];
    rssi = new RSSI[12];

    ids = new char[wap_size][SSID_SIZE]();
    QString str[wap_size];
    str[0] = "Aasdaadsf";
    str[1] = "Badf";
    str[2] = "Casdfsdaf";
    str[3] = "Dddddddd";
    for(unsigned i = 0 ; i < wap_size ; i++)
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

    //this->get_datareader(wap);


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
        QString linkHostMAC = "02:00:00:00:00:30";   //levy
        inputArrayMap(linkHostMAC, input_msg, true);  //levy

        qDebug()<<"input_msg:"<<input_msg;
        //qDebug()<<"split test 1 "<<router1;
        QStringList msg_list = input_msg.split("\n");
        qDebug()<<"msg list=" << msg_list;
        qDebug()<< msg_list[1];
        qDebug()<<"msg list len"<< msg_list.length() << msg_list.size();
        //this->string_filter(QString(input_msg), 1);
        //this->rssi2distance(1);
//        referanceNode(wap_size, wap);
//        view->drawWAPs(wap,wap_size);

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
