// Данный диалог реализует функцию добавление элементов в базу данных посредством сигнала sendData
#ifndef DADDCAR_H
#define DADDCAR_H

#include <QDialog>
namespace Ui {
class DAddCar;
}

class DAddCar : public QDialog
{
    Q_OBJECT
friend class MainWindow;
public:
    explicit DAddCar(QWidget *parent = 0);
    ~DAddCar();
signals:
    void sendData(QString model, QString make, QString power, QString engine, QString year, QString plat);
private slots:
    void on_okButton_toggled(bool checked);
    void okButtonPush();
private:
    Ui::DAddCar *ui;
};

#endif // DADDCAR_H
