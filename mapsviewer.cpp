#include "mapsviewer.h"
#include "ui_mapsviewer.h"

#include <QPainter>
#include <QTime>

MapsViewer::MapsViewer(QWidget *parent) : QWidget(parent), ui(new Ui::MapsViewer){
    ui->setupUi(this);
    rate = 0.75; //長寬限制
    Woutset = (this->width() - (this->width() * rate)) / 2.0; //此始點
    Houtset = (this->height() - (this->height() * rate)) / 2.0;
    this->color = 0;
}
/*
void MapsViewer::drawWAPs(QVector<WAP> waps){

    //宣告、釋放顏色表
    if(this->color != 0)
        free(this->color);
    this->color = new COLOR[waps.size()];

    //設定顏色表
    qsrand(6);
    for(int i=0;i<waps.size();i++){
        //紀錄 RSSI 對應的 WAP index，主要後面處理才能對應
        for(int j=0;j<waps[i].RSSIs.size();j++)
            for(int p=0;p<waps.size();p++)
                if(waps[p].SSID == waps[i].RSSIs[j].SSID)
                    waps[i].RSSIs[j].index = p;

        //set color
        color[i].R = qrand()%256;
        color[i].G = qrand()%256;
        color[i].B = qrand()%256;
    }
    this->waps = waps;
    this->target = target;
    this->repaint();

}*/

void MapsViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    /*
    if(waps.size() <= 0)
        return;

    QPainter painter(this);

    for(int i=0;i<waps.size();i++){
        //draw WAP
        painter.setBrush(QBrush(QColor(color[i].R, color[i].G, color[i].B),Qt::SolidPattern));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(waps[i].location.x() + Woutset, waps[i].location.y() + Houtset,10,10);

        //draw RSSI
        for(int j=0;j<waps[i].RSSIs.size();j++){
            int index = waps[i].RSSIs[j].index;
            //漸層
            QRadialGradient gradient(QPoint((waps[i].location.x() + Woutset), (waps[i].location.y() + Houtset)),
                                     (int)waps[i].RSSIs[j].SS,
                                     QPoint((waps[i].location.x() + Woutset), (waps[i].location.y() + Houtset)));
            gradient.setColorAt(0, QColor::fromRgbF(color[index].R/255.0,
                                                    color[index].G/255.0,
                                                    color[index].B/255.0,
                                                    0.3));
            gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
            painter.setBrush(gradient); //Qt::NoBrush 要取消
            painter.setBrush(Qt::NoBrush);
            pen.setBrush(QColor(color[index].R,color[index].G,color[index].B));
            pen.setWidth(1);
            painter.setPen(pen);
            painter.drawEllipse(QPoint((waps[i].location.x() + Woutset), (waps[i].location.y() + Houtset)),
                                (int)waps[i].RSSIs[j].SS, (int)waps[i].RSSIs[j].SS);
        }
    }
    */
}

MapsViewer::~MapsViewer()
{
    delete ui;
}
