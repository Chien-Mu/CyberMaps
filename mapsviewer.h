#ifndef MAPSVIEWER_H
#define MAPSVIEWER_H

#include <QWidget>
#include <QToolBar>
#include <QPen>
#include <QDebug>

#include "cyberglobal.h"


/* RSSI,Received signal strength indication */
struct vRSSI{
    QString SSID;                   //Source device ID
    unsigned SSID_index;            //Source device tag
    float dBm;                      //Received signal strength
    float distance;
};

struct vLaunch{
    float dBm;                      //wifi signal strength
    float distance;
};

struct vAntenna{
    unsigned rssis_size;
    QVector<vRSSI> rssis;
    QPoint antXY;
    vLaunch lau;
};

/* WAP,Wireless Access Point */
struct vWAP{
    QString SSID;                  //ID
    unsigned index;                //tag
    unsigned antenna_size;
    QVector<vAntenna> ant;
    QPoint wapXY;
};

struct vStyle{
    int R;
    int G;
    int B;
    Qt::BrushStyle bStyle;
};

enum eStyle{
    NoStyle,
    Dense,
    Gradient
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
    void drawWAPs(WAP *waps, const unsigned waps_size);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //ui
    Ui::MapsViewer *ui;

    //螢幕
    float screenRate;
    float Woutset;
    float Houtset;
    float pixelRate;
    float mag; //倍率
    QPen pen;
    volatile bool isSetting;
    volatile bool isVDist;  //is view Distance
    volatile bool isLauch;

    //Style
    vStyle *style;
    volatile eStyle estyle;

    //value
    QVector<vWAP> waps;

private slots:
    void btn_sw_dD_Click();
    void btn_sw_style_Click();
    void changZoom(int value);
    void btn_sw_LR_Click();
};

#endif // MAPSVIEWER_H
