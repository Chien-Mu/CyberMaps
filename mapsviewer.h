#ifndef MAPSVIEWER_H
#define MAPSVIEWER_H

#include <QWidget>
#include <QToolBar>
#include <QPen>
#include <QMenuBar>
#include <QDebug>

#include "cyberglobal.h"
#include "config.h"
#include "QCustomPlot/qcustomplot.h"
#include <QTime>

/* RSSI,Received signal strength indication */
struct vRSSI{
    QString ssid;                   //Source device ID
    unsigned ssid_index;            //Source device tag
    float dBm;                      //Received signal strength
    QTime time;                     //接收到的計時時間
};

struct vDistance{
    QString ssid;                   //Source device ID
    unsigned ssid_index;            //Source device tag
    float distance;
};

struct vLaunch{
    float dBm;                      //wifi signal strength
};

struct vAntenna{
    unsigned rssis_size;
    QVector<vRSSI> rssis;
    QPoint antXY;
    vLaunch lau;
};

/* WAP,Wireless Access Point */
struct vWAP{
    QString ssid;                  //ID
    unsigned index;                //tag
    unsigned dist_size;
    QVector<vDistance> dist;
    unsigned antenna_size;
    QVector<vAntenna> ant;
    QPoint wapXY;
    QPoint realWapXY;
};

struct vlastDistance{
    float distance;
    float realDistance;
    unsigned index1;
    unsigned index2;
    float dBm;                      //拿來計算的rssi
    QTime time;                     //接收到的計時時間
};

struct PlotData{
    QVector<double> x;              //key(time)
    QVector<double> y;              //value(dbm)
    QVector<float> distance;
    QVector<float> realDistance;
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
    void drawWAPs(WAP *waps, const unsigned waps_size, lastDistance *lastDist, const unsigned lastDist_size);

protected:
    void paintEvent(QPaintEvent *event);

private:
    //ui
    Ui::MapsViewer *ui;
    Config *config;
    QMenuBar *menubar;
    QMenu *menu[2];
    QAction *act;

    //plot
    QCustomPlot *plot;
    QCustomPlot *plot2;
    QCustomPlot *plot3;
    PlotData plotData;
    PlotData plot2Data;
    PlotData plot3Data;

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
    QVector<vlastDistance> lastDist;

private slots:
    void triggerMenu(QAction *act);
    void btn_sw_dD_Click();
    void btn_sw_style_Click();
    void changZoom(int value);
    void btn_sw_LR_Click();

signals:
    void throwSetValue(float ab, float bc, float ca);
};

#endif // MAPSVIEWER_H
