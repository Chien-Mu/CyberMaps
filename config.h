#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>
#include <QDoubleValidator>
#include <QKeyEvent>

namespace Ui {
class Config;
}

class Config : public QWidget
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = 0);
    ~Config();

private:
    Ui::Config *ui;
    QDoubleValidator *validDou;
    void keyPressEvent(QKeyEvent *event);

private slots:
    void apply_click();

signals:
    void throwSetValue(float ab, float bc, float ca);
};

#endif // CONFIG_H
