#ifndef MAPSVIEWER_H
#define MAPSVIEWER_H

#include <QWidget>
#include <QPen>

struct RSSI{
    /* RSSI,Received signal strength indication */
    QString SSID;
    float SS;       //signal strength
};

struct WAP{
    /* WAP,Wireless Access Point */
    QString SSID;
    QVector<RSSI> RSSIs;
    QPoint location;
};

struct Target{
    /* PHONE */
    QString SSID;
    RSSI rssi;
    QPoint currentPosition;
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
    void drawWAPs(QVector<WAP> waps);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MapsViewer *ui;
    QVector<WAP> waps;
    Target target;
    QPen pen;
};

#endif // MAPSVIEWER_H
