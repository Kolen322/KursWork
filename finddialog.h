#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include "qcarmodel.h"
namespace Ui {
class findDialog;
}

class findDialog : public QDialog
{
    Q_OBJECT
public:
    explicit findDialog(QWidget *parent = 0);
    ~findDialog();
signals:
    void SfindData(int check, QString str);
private slots:
    void okButtonPush();
private:
    Ui::findDialog *ui;
};

#endif // FINDDIALOG_H
