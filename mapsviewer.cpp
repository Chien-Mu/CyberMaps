#include "mapsviewer.h"
#include "ui_mapsviewer.h"

#include <QPainter>
#include <QTime>
#include <QtMath>

MapsViewer::MapsViewer(QWidget *parent) : QWidget(parent), ui(new Ui::MapsViewer){
    ui->setupUi(this);

    //ui
    connect(ui->btn_sw_style,SIGNAL(clicked()),this,SLOT(btn_sw_style_Click()));
    connect(ui->btn_sw_dD,SIGNAL(clicked()),this,SLOT(btn_sw_dD_Click()));
    connect(ui->btn_sw_LR,SIGNAL(clicked()),this,SLOT(btn_sw_LR_Click()));
    mag = 2.0f/10.0f;
    ui->VS_zoom->setRange(1,100);
    connect(ui->VS_zoom,SIGNAL(valueChanged(int)),this,SLOT(changZoom(int)));
    ui->VS_zoom->setValue(5);

    //畫面長寬限制
    screenRate = 0.3;
    Woutset = this->width() * screenRate; //此始點
    Houtset = this->height() * screenRate;

    this->style = 0;
    this->isSetting = false;
    this->isVDist = true;
    ui->btn_sw_LR->setEnabled(false);
    ui->btn_sw_style->setEnabled(false);
    this->estyle = (eStyle)(0);
    this->isLauch = false;
}

void MapsViewer::changZoom(int value){
    pixelRate = mag * (float)value;
    ui->la_zoom->setText(QString::number(pixelRate) + "x");
    this->update();
}

void MapsViewer::btn_sw_LR_Click(){
    this->isLauch = !isLauch;
    if(isLauch)
        ui->la_sw_LR->setText("Lauch");
    else
        ui->la_sw_LR->setText("RSSI");
    this->update();
}

void MapsViewer::btn_sw_style_Click(){
    int index = (int)estyle;

    if(index == 2)
        index = 0;
    else
        index++;
    estyle = eStyle(index);

    if(index == 0)
        ui->la_sw_style->setText("NoStyle");
    else if(index == 1)
        ui->la_sw_style->setText("Dense");
    else if(index ==2)
        ui->la_sw_style->setText("Gradient");
    this->update();
}

void MapsViewer::btn_sw_dD_Click(){
    isVDist = !isVDist;
    if(isVDist){
        ui->la_sw_dD->setText("Distance");
        ui->btn_sw_LR->setEnabled(false);
        ui->btn_sw_style->setEnabled(false);
    }else{
        ui->la_sw_dD->setText("dBm");
        ui->btn_sw_LR->setEnabled(true);
        ui->btn_sw_style->setEnabled(true);
    }
    this->update();
}

void MapsViewer::drawWAPs(WAP *waps, const unsigned waps_size, lastDistance *lastDist, const unsigned lastDist_size){
    this->isSetting = true;

    //建立風格表
    if(style != 0)
        delete[] style;
    style = new vStyle[waps_size];

    //設定風格表
    unsigned j=8;
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    qsrand(54867);
    for(int i=0;i<(int)waps_size;i++){
        style[i].R = qrand()%256;
        style[i].G = qrand()%256;
        style[i].B = qrand()%256;
        //Dense
        style[i].bStyle = (Qt::BrushStyle)(j++); //8~14
        if(j == 15)
            j=8;
    }


    //clear
    QVector<vWAP>().swap(this->waps);
    QVector<vlastDistance>().swap(this->lastDist);

    //copy to vWAP
    vWAP wap;
    vDistance dist;
    vAntenna ant;
    vRSSI rssi;
    for(unsigned i=0;i<waps_size;i++){
        wap.ssid = waps[i].ssid;
        wap.index = waps[i].index;
        wap.wapXY.setX(waps[i].wapX);
        wap.wapXY.setY(waps[i].wapY);
        wap.realWapXY.setX(waps[i].realWapX);
        wap.realWapXY.setY(waps[i].realWapY);
        wap.dist_size = waps[i].dist_size;
        wap.antenna_size = waps[i].antenna_size;
        this->waps.push_back(wap);
        for(unsigned jj=0;jj<waps[i].dist_size;jj++){
            dist.distance = waps[i].dist[jj].distance;
            dist.ssid = waps[i].dist[jj].ssid;
            dist.ssid_index = waps[i].dist[jj].ssid_index;
            this->waps[i].dist.push_back(dist);
        }
        for(unsigned j=0;j<waps[i].antenna_size;j++){
            ant.antXY.setX(waps[i].ant[j].antX);
            ant.antXY.setY(waps[i].ant[j].antY);
            ant.lau.dBm = waps[i].ant[j].lau.dBm;
            ant.rssis_size = waps[i].ant[j].rssis_size;
            this->waps[i].ant.push_back(ant);
            for(unsigned k=0;k<waps[i].ant[j].rssis_size;k++){
                rssi.dBm = waps[i].ant[j].rssis[k].dBm;
                rssi.ssid = waps[i].ant[j].rssis[k].ssid;
                rssi.ssid_index = waps[i].ant[j].rssis[k].ssid_index;
                this->waps[i].ant[j].rssis.push_back(rssi);
            }    
        }  
    }

    //copy to vlastDistance
    vlastDistance vdist;
    for(unsigned i=0;i<lastDist_size;i++){
        vdist.distance = lastDist[i].distance;
        vdist.realDistance = lastDist[i].realDistance;
        vdist.index1 = lastDist[i].index1;
        vdist.index2 = lastDist[i].index2;
        this->lastDist.push_back(vdist);
    }

    this->isSetting = false;
    this->update();
}

void MapsViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    if(waps.size() <= 0 || this->isSetting)
        return;

    QPainter painter(this);

    //draw Distance
    if(this->isVDist){
        QPointF p1,p2,r1,r2,ptext;
        QString str;
        for(int i=0;i<lastDist.size();i++){
            pen.setBrush(Qt::green);
            painter.setPen(pen);
            r1.setX(waps[lastDist[i].index1].realWapXY.x()*pixelRate+Woutset);
            r1.setY(waps[lastDist[i].index1].realWapXY.y()*pixelRate+Houtset);
            r2.setX(waps[lastDist[i].index2].realWapXY.x()*pixelRate+Woutset);
            r2.setY(waps[lastDist[i].index2].realWapXY.y()*pixelRate+Houtset);
            painter.drawLine(r1,r2);

            pen.setBrush(Qt::yellow);
            painter.setPen(pen);
            p1.setX(waps[lastDist[i].index1].wapXY.x()*pixelRate+Woutset);
            p1.setY(waps[lastDist[i].index1].wapXY.y()*pixelRate+Houtset);
            p2.setX(waps[lastDist[i].index2].wapXY.x()*pixelRate+Woutset);
            p2.setY(waps[lastDist[i].index2].wapXY.y()*pixelRate+Houtset);
            painter.drawLine(p1,p2);

            ptext.setX((p1.x()+p2.x()) / 2.0);
            ptext.setY((p1.y()+p2.y()) / 2.0);
            str = QString::number(lastDist[i].distance,'f',0) + "M";
                  //+ "(" + QString::number(qSqrt(qPow(p1.x()-p2.x(),2) + qPow(p1.y()-p2.y(),2))) + ")";
            painter.drawText(ptext,str);
        }
    }else{
        //draw dBm
        int index;
        float range;
        for(int i=0;i<waps.size();i++){
            for(int j=0;j<waps[i].ant.size();j++){
                if(!isLauch){
                    //draw RSSI
                    for(int k=0;k<waps[i].ant[j].rssis.size();k++){
                        index = waps[i].ant[j].rssis[k].ssid_index;
                        range = waps[i].ant[j].rssis[k].dBm*pixelRate;

                        if(estyle == Gradient){
                            //漸層
                            QRadialGradient gradient(QPoint(waps[i].wapXY.x()*pixelRate+Woutset,
                                                            waps[i].wapXY.y()*pixelRate+Houtset),
                                                     (int)(range),
                                                     QPoint(waps[i].wapXY.x()*pixelRate+Woutset,
                                                            waps[i].wapXY.y()*pixelRate+Houtset));
                            gradient.setColorAt(0, QColor::fromRgbF(style[index].R/255.0,
                                                                    style[index].G/255.0,
                                                                    style[index].B/255.0,
                                                                    0.5));
                            gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
                            painter.setBrush(gradient);
                        }else if(estyle == Dense){
                            //濃密
                            painter.setBrush(QBrush(QColor(style[index].R,style[index].G,style[index].B),
                                                    style[index].bStyle));
                        }else if(estyle == NoStyle){
                            painter.setBrush(Qt::NoBrush);
                        }

                        pen.setBrush(QColor(style[index].R,style[index].G,style[index].B));
                        pen.setWidth(1);
                        painter.setPen(pen);
                        painter.drawEllipse(QPoint(waps[i].wapXY.x()*pixelRate+Woutset,
                                                   waps[i].wapXY.y()*pixelRate+Houtset),
                                            (int)(range),
                                            (int)(range));
                    }
                }else{
                    //draw Lauch
                    range = waps[i].ant[j].lau.dBm*pixelRate;
                    if(estyle == Gradient){
                        //漸層
                        QRadialGradient gradient(QPoint(waps[i].wapXY.x()*pixelRate+Woutset,
                                                        waps[i].wapXY.y()*pixelRate+Houtset),
                                                 (int)(range),
                                                 QPoint(waps[i].wapXY.x()*pixelRate+Woutset,
                                                        waps[i].wapXY.y()*pixelRate+Houtset));
                        gradient.setColorAt(0, QColor::fromRgbF(style[i].R/255.0,
                                                                style[i].G/255.0,
                                                                style[i].B/255.0,
                                                                0.5));
                        gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
                        painter.setBrush(gradient);
                    }else if(estyle == Dense){
                        //濃密
                        painter.setBrush(QBrush(QColor(style[i].R,style[i].G,style[i].B),
                                                style[i].bStyle));
                    }else if(estyle == NoStyle){
                        painter.setBrush(Qt::NoBrush);
                    }

                    pen.setBrush((QColor(style[i].R,style[i].G,style[i].B)));
                    pen.setWidth(1);
                    painter.setPen(pen);
                    painter.drawEllipse(QPoint(waps[i].wapXY.x()*pixelRate+Woutset,
                                               waps[i].wapXY.y()*pixelRate+Houtset),
                                        (int)(range),
                                        (int)(range));
                }
            }
        }
    }

    //draw WAP(另外畫才不會被覆蓋)
    QString dD;
    for(int i=0;i<waps.size();i++){
        painter.setBrush(QBrush(QColor(style[i].R, style[i].G, style[i].B),Qt::SolidPattern));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPoint(waps[i].wapXY.x()*pixelRate+Woutset,
                                   waps[i].wapXY.y()*pixelRate+Houtset),5,5);
        pen.setBrush(Qt::white);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawText(QPoint(waps[i].wapXY.x()*pixelRate+Woutset -10,
                                waps[i].wapXY.y()*pixelRate+Houtset +25),
                         waps[i].ssid);

        if(isLauch && !isVDist){
            pen.setBrush(QColor(style[i].R, style[i].G, style[i].B));
            painter.setPen(pen);
            for(int j=0;j<waps[i].ant.size();j++){
                //顯示天線發射強度
                dD = QString::number(waps[i].ant[j].lau.dBm) + " -dBm";
                painter.drawText(QPoint(waps[i].wapXY.x()*pixelRate+Woutset - 10,
                                        waps[i].wapXY.y()*pixelRate+Houtset + 40 + (j*40)),dD);
            }
        }
    }

    //draw 比率尺
    pen.setBrush(Qt::white);
    pen.setWidth(1);
    painter.setPen(pen);
    int standard = (10.0*pixelRate) + 30;

    painter.drawLine(30, this->height()-20, standard, this->height()-20);  //standard line
    painter.drawLine(30, this->height()-20, 30, this->height()-30); //0
    painter.drawLine(standard, this->height()-20,  standard, this->height()-30); //100
    painter.drawText(30-3, this->height()-35,"0");
    if(isVDist)
        painter.drawText(standard, this->height()-35,"10(M)");
    else
        painter.drawText(standard, this->height()-35,"10(-dBm)");
}

MapsViewer::~MapsViewer()
{
    delete ui;
}
