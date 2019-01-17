#include "qcarmodel.h"

QCarModel::QCarModel( QObject* parent ) : QAbstractTableModel( parent ) {
}

int QCarModel::rowCount(const QModelIndex &parent) const {
    value.GetSize();
}
int QCarModel::columnCount(const QModelIndex &parent) const{
    return 6;
}
QVariant QCarModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if( role != Qt::DisplayRole ) {
          return QVariant();
      }

       if( orientation == Qt::Vertical ) {
           return section;
       }

       switch( section ) {
       case 0:
           return trUtf8( "Производитель" );
       case 1:
           return trUtf8( "Модель" );
       case 2:
           return trUtf8( "Мощность двигателя" );
       case 3:
           return trUtf8( "Двигатель" );
       case 4:
           return trUtf8( "Год производства");
       case 5:
           return trUtf8( "Кузов");
       }

       return QVariant();
}
QVariant QCarModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || value.GetSize() <= index.row() ||
            ( role != Qt::DisplayRole && role != Qt::EditRole )
        ) {
            return QVariant();
        }
  return QVariant(value[index.row()][index.column()]);

}
void QCarModel::addCar(const QString &make, const QString &model, const QString &power, const QString &engine, const QString &year, const QString &plat){
    Car temp;
    temp.SetMake(make);
    temp.SetModel(model);
    temp.SetPower(power);
    temp.SetEngine(engine);
    temp.SetYear(year);
    temp.SetPlay(plat);
    int row = value.GetSize();
    beginInsertRows( QModelIndex(), row, row );
    value.push_back(temp);
    endInsertRows();
    isChanged=true;
}
void QCarModel::addExcelCar(Car temp){
    int row = value.GetSize();
    beginInsertRows(QModelIndex(),row,row);
    value.push_back(temp);
    endInsertRows();
}
void QCarModel::clearTable(){
    int k = value.GetSize();
    while(k>0){
        remove(0);
        k--;
    }
}
/* це объединение таблиц
    int row = value.GetSize();
    beginInsertRows(QModelIndex(),row,row);
    value.push_back(temp);
    endInsertRows();
 */
void QCarModel::remove(int row) {
    int rowselect = 0;
    List::Iterator itr = value.begin();
    do{
        if(rowselect == row){
            beginRemoveRows(QModelIndex(),row,row);
            value.erase(itr);
            endRemoveRows();
            break;
        }
        else{
            itr++;
            rowselect++;
        }

    }while(itr!=nullptr);
    isChanged=true;
}
Qt::ItemFlags QCarModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
            flags |= Qt::ItemIsEditable;
    }
    return flags;
}
bool QCarModel::setData( const QModelIndex& index, const QVariant& value1, int role ) {
    if( !index.isValid() || role != Qt::EditRole  ) {
        return false;
    }
    value.setCar(index.row(),index.column(),value1.toString());
    emit dataChanged( index, index );
    isChanged=true;
    return true;
}
