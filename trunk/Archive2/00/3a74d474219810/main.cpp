#include <iostream>
#include <vector>

using namespace std;


class Handling
{
public:
    virtual void add_car() = 0;
    virtual void erase_car() = 0;
    virtual void show_car(vector<Car> _carvector) = 0;
};


class Car : virtual public Handling
{
public:
    string manufacturer;
    string model;
    string type;
    int engine;
    string enginetype;
    int yearofproduction;
    string geartype;
    int noofgears;
    string price;

    _manufacturer = "Opel";
_model = "Astra";
_type = "Hatchback";
_engine = 1900;
_enginetype = "Diesel";
_yearofproduction = 1999;
_geartype = "Manual";
_noofgears = 5;
_price = "5600";

    Car(){};
    Car(string _manufacturer, string _model, string _type, int _enigne, string _enginetype, int _yearofproduction, string _geartype, int _noofgears, string _price);

    void add_car()
    {

    }

    void erase_car()
    {

    }

    void show_car(vector<Car> _carvector)
    {
        for (int i = 0; i < _carvector.size(); i++)
        {
            cout << "Samochod nr. " << i + 1 << endl;
            cout << "------------------------------" << endl;
            cout << "Marka: " << _carvector[i].manufacturer << endl;
            cout << "Model: " << _carvector[i].model << endl;
            cout << "Typ: " << _carvector[i].type << endl;
            cout << "Pojemnosc silnika: " << _carvector[i].engine << " cm3" << endl;
            cout << "Rodzaj silnika: " << _carvector[i].enginetype << endl;
            cout << "Rok produkcji: " << _carvector[i].yearofproduction << endl;
            cout << "Rodzaj skrzyni biegow: " << _carvector[i].geartype << endl;
            cout << "Liczba biegow: " << _carvector[i].noofgears << endl;
            cout << "Cena: " << _carvector[i].price << " PLN" << endl;
            cout << endl;
        }
    }
};

Car::Car(string _manufacturer, string _model, string _type, int _engine, string _enginetype, int _yearofproduction, string _geartype, int _noofgears, string _price)
    : manufacturer(_manufacturer)
    , model(_model)
    , type(_type)
    , engine(_engine)
    , enginetype(_enginetype)
    , yearofproduction(_yearofproduction)
    , geartype(_geartype)
    , noofgears(_noofgears)
    , price(_price)
{
}

int main()
{
vector<Car> carvector;

Car carobject;

    string _manufacturer;
    string _model;
    string _type;
    int _engine;
    string _enginetype;
    int _yearofproduction;
    string _geartype;
    int _noofgears;
    string _price

carvector.push_back(Car(_manufacturer, _model, _type, _engine, _enginetype,_yearofproduction, _geartype, _noofgears, _price));
carobject.show_car(carvector);

}