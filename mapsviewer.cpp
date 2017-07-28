#include "mapsviewer.h"
#include "ui_mapsviewer.h"

#include <QPainter>
#include <QTime>

MapsViewer::MapsViewer(QWidget *parent) : QWidget(parent), ui(new Ui::MapsViewer){
    ui->setupUi(this);

    //ui
    connect(ui->btn_sw_dD,SIGNAL(clicked()),this,SLOT(btn_sw_dD_Click()));

    rate = 0.75; //長寬限制
    Woutset = (this->width() - (this->width() * rate)) / 2.0; //此始點
    Houtset = (this->height() - (this->height() * rate)) / 2.0;
    this->style = 0;
    this->isSetting = false;
    this->isVDist = false;
}

void MapsViewer::btn_sw_dD_Click(){
    isVDist = !isVDist;
    if(isVDist)
        ui->la_sw_dD->setText("Distance");
    else
        ui->la_sw_dD->setText("dBm");
    this->repaint();
}

void MapsViewer::drawWAPs(WAP *waps, const unsigned waps_size){
    this->isSetting = true;

    //建立風格表
    if(style != 0)
        delete style;
    style = new vStyle[waps_size];

    //設定風格表
    qsrand(6);
    unsigned j=8;
    for(int i=0;i<(int)waps_size;i++){
        style[i].R = qrand()%256;
        style[i].G = qrand()%256;
        style[i].B = qrand()%256;
        style[i].bStyle = (Qt::BrushStyle)(j++); //8~14
        if(j == 15)
            j=8;
    }

    //copy to vWAP
    vWAP wap;
    vAntenna ant;
    vRSSI rssi;
    for(unsigned i=0;i<waps_size;i++){
        wap.SSID = waps[i].SSID[0];
        wap.index = waps[i].index;
        wap.wapXY.setX(waps[i].wapX + Woutset); //順面設定起始點
        wap.wapXY.setY(waps[i].wapY + Houtset);
        wap.antenna_size = waps[i].antenna_size;
        this->waps.push_back(wap);
        for(unsigned j=0;j<waps[i].antenna_size;j++){
            ant.antXY.setX(waps[i].ant[j].antX);
            ant.antXY.setY(waps[i].ant[j].antY);
            ant.lau.dBm = waps[i].ant[j].lau.dBm;
            ant.lau.distance = waps[i].ant[j].lau.distance;
            ant.rssis_size = waps[i].ant[j].rssis_size;
            this->waps[i].ant.push_back(ant);
            for(unsigned k=0;k<waps[i].ant[j].rssis_size;k++){
                rssi.dBm = waps[i].ant[j].rssis[k].dBm;
                rssi.distance = waps[i].ant[j].rssis[k].distance;
                rssi.SSID = waps[i].ant[j].rssis[k].SSID[0];
                rssi.SSID_index = waps[i].ant[j].rssis[k].SSID_index;
                this->waps[i].ant[j].rssis.push_back(rssi);
            }    
        }  
    }
    this->isSetting = false;
    this->repaint();
}

void MapsViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    if(waps.size() <= 0 || this->isSetting)
        return;

    QPainter painter(this);

    int index;
    for(int i=0;i<waps.size();i++){
        for(int j=0;j<waps[i].ant.size();j++){

            //draw RSSI
            for(int k=0;k<waps[i].ant[j].rssis.size();k++){
                index = waps[i].ant[j].rssis[k].SSID_index;
                /*//漸層
                QRadialGradient gradient(QPoint(waps[i].wapXY.x(), waps[i].wapXY.y()),
                                         (int)waps[i].ant[j].rssis[k].dBm,
                                         QPoint(waps[i].wapXY.x(), waps[i].wapXY.y()));
                gradient.setColorAt(0, QColor::fromRgbF(style[index].R/255.0,
                                                        style[index].G/255.0,
                                                        style[index].B/255.0,
                                                        0.5));
                gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
                painter.setBrush(gradient);*/
                /*//Style
                painter.setBrush(QBrush(QColor(style[index].R,style[index].G,style[index].B),
                                        style[index].bStyle));*/
                painter.setBrush(Qt::NoBrush); //啟動樣式此行要註解
                pen.setBrush(QColor(style[index].R,style[index].G,style[index].B));
                pen.setWidth(1);
                painter.setPen(pen);
                if(!this->isVDist)
                    painter.drawEllipse(QPoint(waps[i].wapXY.x(), waps[i].wapXY.y()),
                                        (int)waps[i].ant[j].rssis[k].dBm,
                                        (int)waps[i].ant[j].rssis[k].dBm);
                else
                    painter.drawEllipse(QPoint(waps[i].wapXY.x(), waps[i].wapXY.y()),
                                        (int)waps[i].ant[j].rssis[k].distance,
                                        (int)waps[i].ant[j].rssis[k].distance);
            }
        }
    }

    for(int i=0;i<waps.size();i++){
        //draw WAP(另外畫才不會被覆蓋)
        painter.setBrush(QBrush(QColor(style[i].R, style[i].G, style[i].B),Qt::SolidPattern));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPoint(waps[i].wapXY.x(), waps[i].wapXY.y()),10,10);
        pen.setBrush(Qt::white);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawText(QPoint(waps[i].wapXY.x() -10, waps[i].wapXY.y() +25),waps[i].SSID);
    }
}

MapsViewer::~MapsViewer()
{
    delete ui;
}
