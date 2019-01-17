#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

  QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
      QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
      QCoreApplication::setApplicationName(APPLICATION_NAME);
    QApplication a(argc, argv);
    QSplashScreen *splash =
             new QSplashScreen(QPixmap(":images/splash.png"));
    splash->showMessage(QObject::tr("Загружается, пожалуйста подождите..."),
                    Qt::AlignRight | Qt::AlignBottom, Qt::white);
   splash->show();
    MainWindow w;

    w.show();
splash->finish(&w);
delete splash;
    return a.exec();
}
