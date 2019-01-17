#include "Cars.h"
Car::Car()
{
    make = "null";
    model = "null";
    power = "null";
    engine = "null";
    year = "null";
    plat = "null";
}
QString Car::GetEngine() {
    return engine;
}
Car::Car(const Car & other)
{
    this->model = other.model;
    this->engine = other.engine;
    this->make = other.make;
    this->year = other.year;
    this->plat = other.plat;
    this->power = other.power;
}
QString Car::GetMake() {
    return make;
}
QString Car::GetModel(){
    return model;
}
QString Car::GetPower() {
    return power;
}
QString Car::GetYear() {
    return year;
}
QString Car::GetPlat() {
    return plat;
}
void Car::SetEngine(QString engine) {
    this->engine = engine;
}
void Car::SetMake(QString name) {
    make = name;
}
void Car::SetModel(QString model) {
    this->model = model;
}
void Car::SetPower(QString power) {
    this->power = power;
}
void Car::SetYear(QString year) {
    this->year = year;
}
void Car::SetPlay(QString plat) {
    this->plat = plat;
}
QString Car::operator[](int index) const
{
    switch (index) {
    case 0: return make; break;
    case 1: return model; break;
    case 2: return power; break;
    case 3: return engine; break;
    case 4: return year; break;
    case 5: return plat; break;
    }
}
Car::~Car()
{
}
