#include "daddcar.h"
#include "ui_daddcar.h"

DAddCar::DAddCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DAddCar)
{
    ui->setupUi(this);
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(okButtonPush()));
}

DAddCar::~DAddCar()
{
    delete ui;
}

void DAddCar::on_okButton_toggled(bool checked)
{

}
void DAddCar::okButtonPush(){
    emit sendData(ui->lineMake->text(),ui->lineModel->text(),ui->linePower->text(),ui->lineEngine->text(),ui->lineYear->text(),ui->linePlat->text());
    ui->lineEngine->clear();
    ui->lineMake->clear();
    ui->lineModel->clear();
    ui->linePower->clear();
    ui->lineYear->clear();
    ui->linePlat->clear();
}
