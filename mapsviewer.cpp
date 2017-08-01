#include "mapsviewer.h"
#include "ui_mapsviewer.h"

#include <QPainter>
#include <QTime>

MapsViewer::MapsViewer(QWidget *parent) : QWidget(parent), ui(new Ui::MapsViewer){
    ui->setupUi(this);

    //ui
    connect(ui->btn_sw_style,SIGNAL(clicked()),this,SLOT(btn_sw_style_Click()));
    connect(ui->btn_sw_dD,SIGNAL(clicked()),this,SLOT(btn_sw_dD_Click()));
    connect(ui->btn_sw_LR,SIGNAL(clicked()),this,SLOT(btn_sw_LR_Click()));
    mag = 2.0f/10.0f;
    ui->VS_zoom->setRange(1,10);
    connect(ui->VS_zoom,SIGNAL(valueChanged(int)),this,SLOT(changZoom(int)));
    ui->VS_zoom->setValue(5);


    //畫面長寬限制
    screenRate = 0.75;
    Woutset = (this->width() - (this->width() * screenRate)) / 2.0; //此始點
    Houtset = (this->height() - (this->height() * screenRate)) / 2.0;

    this->style = 0;
    this->isSetting = false;
    this->isVDist = false;
    this->estyle = (eStyle)(0);
    this->isLauch = false;
}

void MapsViewer::changZoom(int value){
    pixelRate = mag * (float)value;
    ui->la_zoom->setText(QString::number(pixelRate) + "x");
    this->repaint();
}

void MapsViewer::btn_sw_LR_Click(){
    this->isLauch = !isLauch;
    if(isLauch)
        ui->la_sw_LR->setText("Lauch");
    else
        ui->la_sw_LR->setText("RSSI");
    this->repaint();
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
    this->repaint();
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
        //Dense
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
        wap.wapXY.setX((waps[i].wapX) + Woutset); //順面設定起始點
        wap.wapXY.setY((waps[i].wapY) + Houtset);
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
    float range;
    for(int i=0;i<waps.size();i++){        
        for(int j=0;j<waps[i].ant.size();j++){
            if(!isLauch){
                //draw RSSI
                for(int k=0;k<waps[i].ant[j].rssis.size();k++){
                    index = waps[i].ant[j].rssis[k].SSID_index;
                    if(this->isVDist)
                        range = waps[i].ant[j].rssis[k].distance*pixelRate;
                    else
                        range = waps[i].ant[j].rssis[k].dBm*pixelRate;



                    if(estyle == Gradient){
                        //漸層
                        QRadialGradient gradient(QPoint(waps[i].wapXY.x()*pixelRate, waps[i].wapXY.y()*pixelRate),
                                                 (int)(range),
                                                 QPoint(waps[i].wapXY.x()*pixelRate, waps[i].wapXY.y()*pixelRate));
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
                    painter.drawEllipse(QPoint(waps[i].wapXY.x()*pixelRate, waps[i].wapXY.y()*pixelRate),
                                        (int)(range),
                                        (int)(range));
                }
            }else{
                //draw Lauch
                if(this->isVDist)
                    range = waps[i].ant[j].lau.distance*pixelRate;
                else
                    range = waps[i].ant[j].lau.dBm*pixelRate;

                if(estyle == Gradient){
                    //漸層
                    QRadialGradient gradient(QPoint(waps[i].wapXY.x()*pixelRate, waps[i].wapXY.y()*pixelRate),
                                             (int)(range),
                                             QPoint(waps[i].wapXY.x()*pixelRate, waps[i].wapXY.y()*pixelRate));
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
                painter.drawEllipse(QPoint(waps[i].wapXY.x()*pixelRate, waps[i].wapXY.y()*pixelRate),
                                    (int)(range),
                                    (int)(range));
            }
        }
    }

    //draw WAP(另外畫才不會被覆蓋)
    QString dD;
    for(int i=0;i<waps.size();i++){
        painter.setBrush(QBrush(QColor(style[i].R, style[i].G, style[i].B),Qt::SolidPattern));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPoint(waps[i].wapXY.x()*pixelRate, waps[i].wapXY.y()*pixelRate),5,5);
        pen.setBrush(Qt::white);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawText(QPoint(waps[i].wapXY.x()*pixelRate -10, waps[i].wapXY.y()*pixelRate +25),
                         waps[i].SSID);

        if(isLauch){
            pen.setBrush(QColor(style[i].R, style[i].G, style[i].B));
            painter.setPen(pen);
            for(int j=0;j<waps[i].ant.size();j++){
                //顯示天線發射強度
                if(isVDist)
                    dD = QString::number(waps[i].ant[j].lau.distance) + " dist";
                else
                    dD = QString::number(waps[i].ant[j].lau.dBm) + " dBm";

                painter.drawText(QPoint(waps[i].wapXY.x()*pixelRate - 10,
                                        waps[i].wapXY.y()*pixelRate + 40 + (j*40)),dD);
            }
        }
    }

    //draw 比率尺
    pen.setBrush(Qt::white);
    pen.setWidth(1);
    painter.setPen(pen);
    int standard = (100.0*pixelRate) + 30;

    painter.drawLine(30, this->height()-20, standard, this->height()-20);  //standard line
    painter.drawLine(30, this->height()-20, 30, this->height()-30); //0
    painter.drawLine(standard, this->height()-20,  standard, this->height()-30); //100
    painter.drawText(30-3, this->height()-35,"0");
    painter.drawText(standard - 10, this->height()-35,"100");
}

MapsViewer::~MapsViewer()
{
    delete ui;
}
