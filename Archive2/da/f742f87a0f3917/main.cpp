#include <cstdlib>
#include <iostream>
#include <string>               
#include <iomanip>

using namespace std;

class ParkingMeter

{
private:

    double timePurchased;

public:

    // constructor
    ParkingMeter(double tp)
    {
        timePurchased = tp;
    }

    void setTP(double);

    double getTP() const;

};


class PoliceOfficer

{
private:

    string  offName;
    double     offBadge;
    double  parkMin, meterPurchased, meterTime;

public:

// constructor
    PoliceOfficer(string n, double b)
    {
        offName = n;
        offBadge = b;
    }

    void setON(string);
    void setOB(int);

    string getON() const;
    int getOB() const;

};



class ParkedCar

{
private:

    string make, model, color, lplate;
    double numMinutes;    

public:

    //constructor

    ParkedCar(string ma, string mo, string co, string lp, double min)
    {
        make = ma;
        model = mo;
        color = co;
        lplate = lp;
        numMinutes = min;
    }

    void setMake(string);
    void setModel(string);
    void setColor(string);
    void setLplate(string);
    void setNumMinutes(double);

    string getMake() const;
    string getModel() const;
    string getColor() const;
    string getLplate() const;
    double getNumMinutes() const;


};

class ParkingTicket

{
private:



public:

    void generateticket() const;

    double PoliceOfficer(string, double);
    double ParkedCar(string, string, string, string, double);
    double ParkingMeter(double);




};

int main()
{

    ParkingTicket   PT;

    PT.generateticket();


    return 0;    
}




void ParkedCar::setMake(string ma)
{
    make = ma;
}

void ParkedCar::setModel(string mo)
{
    model = mo;
}

void ParkedCar::setColor(string co)
{
    color = co;
}

void ParkedCar::setLplate(string lp)
{
    lplate = lp;
}

void ParkedCar::setNumMinutes(double nm)
{
    if (nm > 0)
        numMinutes = nm;
    else
    {
        cout << "invalid number of minutes (must be > 0) \n";
        exit(EXIT_FAILURE);
    }
}

string ParkedCar::getMake() const
{
    return make;
}

string ParkedCar::getModel() const
{
    return model;
}

 string ParkedCar::getColor() const
{
   return color;
}

string ParkedCar::getLplate() const
{
    return lplate;
}

double ParkedCar::getNumMinutes() const
{
    return numMinutes;
}


void ParkingTicket::generateticket() const
{
    ParkedCar::ParkedCar  car("GMC","Yukon XL","Grey","111111",9999);
    PoliceOfficer::PoliceOfficer bacon("Blake Peebles",9999);               
    ParkingMeter::ParkingMeter pm(55);

    if (car.getNumMinutes() > pm.getTP())
    {
        double time4fine = car.getNumMinutes() - pm.getTP();
        double fine;

        if (time4fine < 60)
            { fine = 25; }
        else
        {
            time4fine = (time4fine/60 - 1);
            fine = 25+(time4fine*10);
        }

        cout << "For the " << car.getColor() << " " << car.getMake() << " " <<           car.getModel() << " " << "License # " << car.getLplate() << endl;
    cout << "Officer " << bacon.getON() << " " << "Badge Number: " << bacon.getOB() <<     endl;
    cout << "issued a citation: \n" << endl;
    cout << "Your fine is: $" << fine << endl; 

    }
    else
        cout << "No ticket issued" << endl; 
    }


void ParkingMeter::setTP(double t)
{
    if (t > 0)
        timePurchased = t;
    else
    {
        cout << "invalid number of minutes (must be > 0) \n";
        exit(EXIT_FAILURE);
    }
}

double ParkingMeter::getTP() const
{
    return timePurchased;
}


void PoliceOfficer::setOB(int ob)
{
    if (ob > 0)
        offBadge = ob;
    else
    {
        cout << "invalid number of minutes (must be > 0) \n";
        exit(EXIT_FAILURE);
    }
}

void PoliceOfficer::setON(string n)
{
    offName = n;
}

int PoliceOfficer::getOB() const
{
    return offBadge;
}

string PoliceOfficer::getON() const
{
    return offName;
}