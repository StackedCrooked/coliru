


class Vehicle {
public:
    Vehicle(int a): val(a) {}
    virtual ~Vehicle() {}
    virtual void setVal(int i) = 0;
    virtual int getVal() = 0;
protected:
int val;

};


class Car : public Vehicle {
public:
    Car(int a) : Vehicle(a) {}
    ~Car() {}
    virtual void setVal(int i);
    virtual int getVal();
};

//************I SPeCULATE THAT THESE EXIST?
void Car::setVal(int i) 
{val = i;}

int Car::getVal() 
{return val;}
//******************************************

#include <iostream>
    using namespace std;

int main()
{
    Vehicle * car1 = new Car(0);
    Vehicle * car2 = new Car(1);
    cout << "val car1 :"<< car1->getVal() << endl; 
    cout << "val car2 :"<< car2->getVal() << endl; 
    car1 = car2;
    cout << "val car1 :"<< car1->getVal() << endl; 
    cout << "val car2 :"<< car2->getVal() << endl; 
    car2->setVal(6);
    cout << "val car1 :"<< car1->getVal() << endl; 
    cout << "val car2 :"<< car2->getVal() << endl;
    car1->setVal(-1);
    cout << "val car1 :"<< car1->getVal() << endl; 
    cout << "val car2 :"<< car2->getVal() << endl;
    return 0;
}