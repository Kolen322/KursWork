#ifndef QCARMODEL_H
#define QCARMODEL_H
#include "Cars.h"
#include "List.h"
#include "daddcar.h"

#include <QAbstractTableModel>
#include <QVariant>
#include <QString>
#include <QItemSelectionModel>
#include <QModelIndexList>
class QCarModel : public QAbstractTableModel
{
    Q_OBJECT
    friend class MainWindow;
public:
    QCarModel( QObject* parent = 0 );
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
   QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void addCar(const QString& make,const QString& model,const QString& power,const QString& engine, const QString& year, const QString& plat );
    void remove(int row);
    void addExcelCar(Car temp);
    void clearTable();
private:
    List value;
    Car f;
    bool isChanged = false;
signals:

public slots:
};

#endif // QCARMODEL_H
