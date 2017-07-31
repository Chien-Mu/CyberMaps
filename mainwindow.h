#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "mapsviewer.h"
#include "cyberglobal.h"
#include "datareader.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    dataReader *datareader;

private:
    Ui::MainWindow *ui;
    MapsViewer *view;
};

#endif // MAINWINDOW_H
