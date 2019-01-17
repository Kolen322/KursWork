#ifndef CARS_H
#define CARS_H
#include <iostream>
#include <string>
#include <QString>
using namespace std;
class Car
{
public:
    Car();
    Car(QString make, QString model, QString power, QString engine, QString year, QString plat) : make(make),model(model),power(power),engine(engine),year(year),plat(plat) {}
    Car(const Car &other);
   // string &operator[](int index);
    QString GetMake();
    QString GetModel();
    QString GetPower();
    QString GetEngine();
    QString GetYear();
    QString GetPlat();
    void SetMake(QString name);
    void SetModel(QString model);
    void SetPower(QString power);
    void SetEngine(QString engine);
    void SetYear(QString year);
    void SetPlay(QString plat);
    QString operator[](int index) const;
    ~Car();
private:
    QString make;
    QString model;
    QString power;
    QString engine;
    QString year;
    QString plat;
};



#endif // CARS_H
