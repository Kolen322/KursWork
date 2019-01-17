#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QCloseEvent>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxwidget.h>
#include <QSplashScreen>
#include "qcarmodel.h"
#include "daddcar.h"
#include "finddialog.h"
#define ORGANIZATION_NAME "Kolen Inc"
#define ORGANIZATION_DOMAIN "SPBSUT"
#define APPLICATION_NAME "CarBase"
class Spreadsheet;
class QCarModel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class QCarModel;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void receiveData(QString make,QString model, QString power, QString engine, QString year, QString plat); // взаимодейтсвие с диалогом DAddCar
    void removeRows();
    void getFind(int row,QString str);
    void open();
    bool saveFile();
    bool saveAs();
    bool save();
    void copy();
    void paste();
    void cut();
    void append();
    void about();
    void aboutQt();
    void faq();
    void nfindpush();
    void pfindpush();
    void newFile();
private:
        void createToolBar();
    void setConnection();
    void setStatusBar();
    bool maybeSave();
        void Excel();
    void setCurrentFile(const QString &Name);

private:
    Ui::MainWindow *ui;
    QCarModel *t_model;
    bool isOpen = false;
    bool isSaveAs = false;
    Car *buffer;
    QString fileBuffer = "";
    QString findBuffer;
    int sizeBuffer;
    QToolBar *ToolBar;
    //QStatusBar statusBar;
    QString fileName;
    // Всё что ниже нужно для работы с файлами Excel
    QAxWidget *excel;
    QAxObject *workbooks;
    QAxObject *workbook;
    QAxObject *sheet;
    QAxObject *cell;
    int mRows;
    Car temp;
    QString data;
};

#endif // MAINWINDOW_H
