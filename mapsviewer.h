#ifndef MAPSVIEWER_H
#define MAPSVIEWER_H

#include <QWidget>
#include <QPen>
#include <QDebug>

struct COLOR{
    int R;
    int G;
    int B;
};

namespace Ui {
class MapsViewer;
}

class MapsViewer : public QWidget
{
    Q_OBJECT

public:
    explicit MapsViewer(QWidget *parent = 0);
    ~MapsViewer();
    //void drawWAPs(QVector<WAP> waps);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MapsViewer *ui;

    //螢幕
    float rate;
    float Woutset;
    float Houtset;
    QPen pen;

    //Color
    COLOR *color;

    //value
    //QVector<WAP> waps;



};

#endif // MAPSVIEWER_H
