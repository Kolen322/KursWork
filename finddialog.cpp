#include "finddialog.h"
#include "ui_finddialog.h"

findDialog::findDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findDialog)
{
    ui->setupUi(this);
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(okButtonPush()));
}

findDialog::~findDialog()
{
    delete ui;
}
void findDialog::okButtonPush(){
    if(ui->allText->isChecked()){
        emit SfindData(0,ui->findEdit->text());
    }
    else if(ui->nextText->isChecked()){
        emit SfindData(1,ui->findEdit->text());
    }
    else {
        emit SfindData(2,ui->findEdit->text());
    }
}
