#include "mapsviewer.h"
#include "ui_mapsviewer.h"

#include <QPainter>
#include <QTime>
#include <QtMath>

MapsViewer::MapsViewer(QWidget *parent) : QWidget(parent), ui(new Ui::MapsViewer){
    ui->setupUi(this);

    //ui
    config = new Config;
    menu[0] = new QMenu("Config");
    menu[0]->addAction("Setting");
    menubar = new QMenuBar(this);
    menubar->addMenu(menu[0]);
    connect(this->menu[0],SIGNAL(triggered(QAction*)),this,SLOT(triggerMenu(QAction*)));
    connect(ui->btn_sw_style,SIGNAL(clicked()),this,SLOT(btn_sw_style_Click()));
    connect(ui->btn_sw_dD,SIGNAL(clicked()),this,SLOT(btn_sw_dD_Click()));
    connect(ui->btn_sw_LR,SIGNAL(clicked()),this,SLOT(btn_sw_LR_Click()));
    mag = 2.0f/10.0f;
    ui->VS_zoom->setRange(1,200);
    connect(ui->VS_zoom,SIGNAL(valueChanged(int)),this,SLOT(changZoom(int)));
    ui->VS_zoom->setValue(5);

    //畫面長寬限制
    screenRate = 0.3;
    Woutset = this->width() * screenRate; //此始點
    Houtset = this->height() * screenRate;

    this->style = 0;
    this->isSetting = false;
    this->isVDist = true;
    ui->la_sw_dD->setText("Distance");
    ui->btn_sw_LR->setEnabled(false);
    ui->btn_sw_style->setEnabled(false);
    this->estyle = (eStyle)(0);
    this->isLauch = false;

    //config return value
    connect(config,SIGNAL(throwSetValue(float,float,float)),this,SIGNAL(throwSetValue(float,float,float)));

    //plot
    this->plot = ui->plot;
    this->plot2 = ui->plot_2;
    this->plot3 = ui->plot_3;
    this->plot->addGraph();
    this->plot2->addGraph();
    this->plot3->addGraph();
    //----------------------plot----------------------
    //interaction
    this->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //bebel
    this->plot->xAxis2->setVisible(true);
    this->plot->xAxis2->setTickLabels(false);
    this->plot->xAxis2->setTicks(false);
    this->plot->xAxis2->setLabel("A-B");
    this->plot->xAxis2->setLabelColor(Qt::white);
    this->plot->yAxis->setLabel("dbm");
    this->plot->yAxis->setLabelColor(Qt::white);
    //tick
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    this->plot->xAxis->setTicker(timeTicker);
    this->plot->xAxis->ticker()->setTickCount(3);
    this->plot->xAxis->setBasePen(QPen(Qt::white, 1));
    this->plot->yAxis->setBasePen(QPen(Qt::white, 1));
    this->plot->xAxis->setTickPen(QPen(Qt::white, 1));
    this->plot->yAxis->setTickPen(QPen(Qt::white, 1));
    this->plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    this->plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    this->plot->xAxis->setTickLabelColor(Qt::white);
    this->plot->yAxis->setTickLabelColor(Qt::white);
    //line
    this->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    this->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::red), 9));
    this->plot->graph(0)->setPen(QPen(Qt::red));
    //透明
    this->plot->setAttribute(Qt::WA_TranslucentBackground);
    this->plot->setStyleSheet("background:transparent");
    this->plot->setBackground(QBrush(Qt::NoBrush));

    //----------------------plot2----------------------
    //interaction
    this->plot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //bebel
    this->plot2->xAxis2->setVisible(true);
    this->plot2->xAxis2->setTickLabels(false);
    this->plot2->xAxis2->setTicks(false);
    this->plot2->xAxis2->setLabel("A-C");
    this->plot2->xAxis2->setLabelColor(Qt::white);
    this->plot2->yAxis->setLabel("dbm");
    this->plot2->yAxis->setLabelColor(Qt::white);
    //tick
    this->plot2->xAxis->setTicker(timeTicker);
    this->plot2->xAxis->ticker()->setTickCount(3);
    this->plot2->xAxis->setBasePen(QPen(Qt::white, 1));
    this->plot2->yAxis->setBasePen(QPen(Qt::white, 1));
    this->plot2->xAxis->setTickPen(QPen(Qt::white, 1));
    this->plot2->yAxis->setTickPen(QPen(Qt::white, 1));
    this->plot2->xAxis->setSubTickPen(QPen(Qt::white, 1));
    this->plot2->yAxis->setSubTickPen(QPen(Qt::white, 1));
    this->plot2->xAxis->setTickLabelColor(Qt::white);
    this->plot2->yAxis->setTickLabelColor(Qt::white);
    //line
    this->plot2->graph(0)->setLineStyle(QCPGraph::lsLine);
    this->plot2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::red), 9));
    this->plot2->graph(0)->setPen(QPen(Qt::red));
    //透明
    this->plot2->setAttribute(Qt::WA_TranslucentBackground);
    this->plot2->setStyleSheet("background:transparent");
    this->plot2->setBackground(QBrush(Qt::NoBrush));

    //----------------------plot3----------------------
    //interaction
    this->plot3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //bebel
    this->plot3->xAxis2->setVisible(true);
    this->plot3->xAxis2->setTickLabels(false);
    this->plot3->xAxis2->setTicks(false);
    this->plot3->xAxis2->setLabel("B-C");
    this->plot3->xAxis2->setLabelColor(Qt::white);
    this->plot3->yAxis->setLabel("dbm");
    this->plot3->yAxis->setLabelColor(Qt::white);
    //tick
    this->plot3->xAxis->setTicker(timeTicker);
    this->plot3->xAxis->ticker()->setTickCount(3);
    this->plot3->xAxis->setBasePen(QPen(Qt::white, 1));
    this->plot3->yAxis->setBasePen(QPen(Qt::white, 1));
    this->plot3->xAxis->setTickPen(QPen(Qt::white, 1));
    this->plot3->yAxis->setTickPen(QPen(Qt::white, 1));
    this->plot3->xAxis->setSubTickPen(QPen(Qt::white, 1));
    this->plot3->yAxis->setSubTickPen(QPen(Qt::white, 1));
    this->plot3->xAxis->setTickLabelColor(Qt::white);
    this->plot3->yAxis->setTickLabelColor(Qt::white);
    //line
    this->plot3->graph(0)->setLineStyle(QCPGraph::lsLine);
    this->plot3->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::red), 9));
    this->plot3->graph(0)->setPen(QPen(Qt::red));
    //透明
    this->plot3->setAttribute(Qt::WA_TranslucentBackground);
    this->plot3->setStyleSheet("background:transparent");
    this->plot3->setBackground(QBrush(Qt::NoBrush));
}

void MapsViewer::changZoom(int value){
    pixelRate = mag * (float)value;
    ui->la_zoom->setText(QString::number(pixelRate) + "x");
    this->update();
}

void MapsViewer::triggerMenu(QAction *act){
    if(act->text() == "Setting"){
        config->show();
        config->raise();
    }
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
                rssi.time = QTime::fromMSecsSinceStartOfDay(waps[i].ant[j].rssis[k].time);
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
        vdist.dBm = lastDist[i].dBm;
        vdist.time = QTime::fromMSecsSinceStartOfDay(lastDist[i].time);
        this->lastDist.push_back(vdist);

        if(i==0){
            this->plotData.x.push_back(lastDist[i].time/1000.0);
            this->plotData.y.push_back(lastDist[i].dBm);
            this->plotData.distance.push_back(lastDist[i].distance);
            this->plotData.realDistance.push_back(lastDist[i].realDistance);
        }else if(i==1){
            this->plot2Data.x.push_back(lastDist[i].time/1000.0);
            this->plot2Data.y.push_back(lastDist[i].dBm);
            this->plot2Data.distance.push_back(lastDist[i].distance);
            this->plot2Data.realDistance.push_back(lastDist[i].realDistance);
        }else if(i==2){
            this->plot3Data.x.push_back(lastDist[i].time/1000.0);
            this->plot3Data.y.push_back(lastDist[i].dBm);
            this->plot3Data.distance.push_back(lastDist[i].distance);
            this->plot3Data.realDistance.push_back(lastDist[i].realDistance);
        }
    }
    //plot
    this->plot->graph(0)->setData(this->plotData.x, this->plotData.y);
    this->plot2->graph(0)->setData(this->plot2Data.x, this->plot2Data.y);
    this->plot3->graph(0)->setData(this->plot3Data.x, this->plot3Data.y);
    this->plot->graph(0)->rescaleAxes(false);
    this->plot2->graph(0)->rescaleAxes(false);
    this->plot3->graph(0)->rescaleAxes(false);
    //rpQueuedReplot 可以避免 main form 在 repaint 時，plot 若也在執行 replot 會導致當掉
    plot->replot(QCustomPlot::rpQueuedReplot);
    plot2->replot(QCustomPlot::rpQueuedReplot);
    plot3->replot(QCustomPlot::rpQueuedReplot);

    //main form repaint
    this->isSetting = false;
    this->update();
}

void MapsViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    if(waps.size() <= 0 || this->isSetting)
        return;

    QPainter painter;
    painter.begin(this);

    //draw Distance
    if(this->isVDist){
        QPoint p1,p2,r1,r2,ptext;
        QString str;
        for(int i=0;i<lastDist.size();i++){
            pen.setBrush(Qt::gray);
            pen.setStyle(Qt::DotLine);
            painter.setPen(pen);
            r1.setX((int)waps[lastDist[i].index1].realWapXY.x()*pixelRate+Woutset);
            r1.setY((int)waps[lastDist[i].index1].realWapXY.y()*pixelRate+Houtset);
            r2.setX((int)waps[lastDist[i].index2].realWapXY.x()*pixelRate+Woutset);
            r2.setY((int)waps[lastDist[i].index2].realWapXY.y()*pixelRate+Houtset);
            painter.drawLine(r1,r2);

            pen.setBrush(Qt::yellow);
            pen.setStyle(Qt::SolidLine);
            painter.setPen(pen);
            p1.setX((int)waps[lastDist[i].index1].wapXY.x()*pixelRate+Woutset);
            p1.setY((int)waps[lastDist[i].index1].wapXY.y()*pixelRate+Houtset);
            p2.setX((int)waps[lastDist[i].index2].wapXY.x()*pixelRate+Woutset);
            p2.setY((int)waps[lastDist[i].index2].wapXY.y()*pixelRate+Houtset);
            painter.drawLine(p1,p2);

            ptext.setX((p1.x()+p2.x()) / 2.0);
            ptext.setY((p1.y()+p2.y()) / 2.0);

            if(lastDist[i].realDistance != 0){
                //誤差率 = 誤差=( |理論-實驗|/理論 )*100% ,for Julia
                float deviaiton = (qAbs(lastDist[i].realDistance - lastDist[i].distance) / lastDist[i].realDistance)*100;
                str = QString::number(deviaiton,'f',0) + "% (" +
                        QString::number(lastDist[i].distance,'g',4) + "/" +
                        QString::number(lastDist[i].realDistance,'g',4) + "M)";
                //+ "(" + QString::number(qSqrt(qPow(p1.x()-p2.x(),2) + qPow(p1.y()-p2.y(),2))) + ")";
                painter.drawText(ptext,str);
            }
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

        if(this->isVDist){
            pen.setWidth(2);
            painter.setPen(pen); //為了在圓周畫線
            painter.drawEllipse(QPoint(waps[i].realWapXY.x()*pixelRate+Woutset,
                                        waps[i].realWapXY.y()*pixelRate+Houtset),5,5);
        }
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPoint(waps[i].wapXY.x()*pixelRate+Woutset,
                                   waps[i].wapXY.y()*pixelRate+Houtset),5,5);

        pen.setBrush(Qt::white);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawText(QPoint(waps[i].wapXY.x()*pixelRate+Woutset -10,
                                waps[i].wapXY.y()*pixelRate+Houtset +25),
                         waps[i].ssid.right(2));

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
    painter.end();
}

MapsViewer::~MapsViewer()
{
    delete ui;
}
