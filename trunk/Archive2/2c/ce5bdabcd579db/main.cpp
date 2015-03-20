//    #pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Payroll {
private:


    int empNumber;
    string name;
    double  hours;
    double payRate;
    double grossPay;

    int *aptr;
    int arraySize;

public:



    Payroll(int size);
    Payroll();
    Payroll(const Payroll & aPayroll);
    ~Payroll();

    //Mutators

    void setVector(Payroll &aPayroll);

    void setEmpNumber(int empNumber);

    void setName(string name);

    void setHours(double hours);

    void setPayRate(double payRate);

    void setGrossPay(double grossPay);
    //Accessors

    int getEmpNumber()const;

    string getName()const;

    double getHours()const;

    double getPayRate()const;

    double getGrossPay()const;

    Payroll &operator =(const Payroll &aPayroll);

    bool operator ==(const Payroll &aPayroll) const;


    friend ostream & operator << (ostream & output, const Payroll & aPayroll);

    friend istream & operator >> (istream & input, Payroll & aPayroll);


};

//cpp

Payroll::Payroll() : empNumber(0), name(""), hours(0.00), payRate(0.00), grossPay(0.00) {}


Payroll::Payroll(const Payroll & aPayroll) : empNumber(aPayroll.empNumber), name(aPayroll.name), hours(aPayroll.hours),
payRate(aPayroll.payRate), grossPay(aPayroll.grossPay) {}



Payroll::~Payroll() {

}

//Mutators

void Payroll::setEmpNumber(int empNumber) {
    this->empNumber = empNumber;
}

void Payroll::setName(string name) {
    this->name = name;
}


void Payroll::setHours(double hours) {
    this->hours = hours;
}

void Payroll::setPayRate(double payRate) {
    this->payRate = payRate;
}

void Payroll::setGrossPay(double  grossPay) {
    this->grossPay = grossPay;
}

//Accessors

int Payroll::getEmpNumber()const {
    return(this->empNumber);
}


string Payroll::getName()const {
    return(this->name);
}


double Payroll::getHours()const {
    return(this->hours);
}


double Payroll::getPayRate()const {
    return(this->payRate);
}

double Payroll::getGrossPay()const {

    return(this-> hours * payRate);
}

Payroll &Payroll::operator = (const Payroll &aPayroll) {

    this->name = aPayroll.name;
    this->empNumber = aPayroll.empNumber;
    this->hours = aPayroll.hours;
    this->payRate = aPayroll.payRate;
    this->grossPay = aPayroll.grossPay;

    return(*this);


}

bool Payroll::operator ==(const Payroll &aPayroll) const {

    bool equal = this->name == aPayroll.name;

    return(equal);


}

#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

#include <iostream>
#include <cstdlib>
using namespace std;


template <class type>
class SimpleVector {

private:
    type *aptr;
    int arraySize;
    void subError();

public:
    SimpleVector(int);
    SimpleVector(const SimpleVector &aVector);
    ~SimpleVector();
    int size() {
        return arraySize;
    }

    type &operator [](int);
    void print();

};

template <class type>
SimpleVector<type>::SimpleVector(int s) {

    arraySize = s;
    aptr = new type[s];
    for (int count = 0; count < arraySize; count++)
        aptr[count] = type();
}

template <class type>
SimpleVector<type>::SimpleVector(const SimpleVector &aVector) {

    arraySize = aVector.arraySize;
    aptr = new type[arraySize];
    for (int count = 0; count < arraySize; count++)
        aptr[count] = aVector[count];
}

template <class type>
SimpleVector<type>::~SimpleVector(){

    if (arraySize > 0)
        delete[] aptr;
}

template <class type>
void SimpleVector<type>::subError() {
    cout << "ERROR: Subscript out of range.\n";
    exit(0);
}

template <class type>
type &SimpleVector<type>::operator[](int sub) {

    if (sub < 0 || sub >= arraySize)
        subError();

    return aptr[sub];
}

template <class type>
void SimpleVector<type>::print() {

    for (int k = 0; k < arraySize; k++)
        cout << aptr[k] << " ";
    cout << endl;
}


#endif

#ifndef SortingVector_h
#define SortingVector_h

#include <iostream>
#include <string>

template <class t>
class SortingVector : public SimpleVector<t> {

public:
    SortingVector(int s) : SimpleVector<t>(s) {}
    SortingVector(SortingVector &aSort);
    SortingVector(SimpleVector<t> &aVector) : SimpleVector<t>(aVector) {}

    void sortingByName(SimpleVector<Payroll> &aVector);




};
#endif


template <class t>
SortingVector<t>::SortingVector(SortingVector &aVector) : SimpleVector<t>(aVector) {}

template <class t>
void SortingVector<t>::sortingByName(SimpleVector<Payroll> &aVector) {

    bool swap;
    SortingVector<Payroll> temp();

    int x;

    do {

        swap = false;
        for (int i = 0; i < aVector.arraySize; i++) {


            x = strcmp(aVector[i], aVector[i + 1]);
            if (x > 0) {

                temp[i] = aVector[i];
                aVector[i] = aVector[i + 1];
                aVector[i + 1] = temp[i];
                swap = true;

            }
        }
    } while (swap);

}