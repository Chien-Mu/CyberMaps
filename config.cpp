#include "config.h"
#include "ui_config.h"
#include <QDebug>

Config::Config(QWidget *parent) : QWidget(parent), ui(new Ui::Config){
    ui->setupUi(this);

    //驗證器
    validDou = new QDoubleValidator(this); //驗證器，限制只能輸入福點數
    ui->LE_ab->setValidator(validDou);
    ui->LE_bc->setValidator(validDou);
    ui->LE_ca->setValidator(validDou);

    connect(ui->btn_apply,SIGNAL(clicked()),this,SLOT(apply_click()));
}

void Config::apply_click(){
    float ab,bc,ca;
    ab = ui->LE_ab->text().toFloat();
    bc = ui->LE_bc->text().toFloat();
    ca = ui->LE_ca->text().toFloat();
    emit throwSetValue(ab, bc, ca);
    this->close();
}

void Config::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        apply_click();
}

Config::~Config()
{
    delete ui;
}
