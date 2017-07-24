#include "mapsviewer.h"
#include "ui_mapsviewer.h"

#include <QPainter>

MapsViewer::MapsViewer(QWidget *parent) : QWidget(parent), ui(new Ui::MapsViewer){
    ui->setupUi(this);
}

void MapsViewer::drawWAPs(QVector<WAP> waps){
    this->waps = waps;
    this->target = target;
    this->repaint();
}

void MapsViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    if(waps.size() <= 0)
        return;

    QPainter painter(this);

    pen.setBrush(Qt::yellow);
    pen.setWidth(2);
    //painter.setPen(pen);

    for(int i=0;i<waps.size();i++){
        painter.setBrush(QBrush(QColor(255,0,0),Qt::SolidPattern));
        painter.drawEllipse(waps[i].location.x(),waps[i].location.y(),5,5);
    }


}

MapsViewer::~MapsViewer()
{
    delete ui;
}
