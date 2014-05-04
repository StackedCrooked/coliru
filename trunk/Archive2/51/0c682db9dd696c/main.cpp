#ifndef BasisToestand_H 
#define BasisToestand_H

   #include<vector>
   using std::vector;
   #include <string>
   using std::string;


class BasisToestand
{

public:

    BasisToestand (const string="geen naam");   
    virtual ~BasisToestand();           

    //void setName( const string );

    // Get Functions are all declared const
    const string getName() const;
    virtual const double getVal(double) const = 0;             //THIS WORKS
    //virtual const vector<double> Toestand(int) const = 0;    //THIS DOES NOT

    // Overloaded operators is also declared const and virtual
    virtual const double operator()(double = 0.) const = 0;    //THIS WORKS



private:

    string T_Naam;

};

#endif

//Base class cpp:

#include <iostream>
using std::cout;
using std::endl;

#include<vector>
using std::vector;
#include <string>
using std::string;
#include <cstdlib>
using std::exit;

//#include "BasisToestand.h"

BasisToestand::BasisToestand (const string nieuwe_naam) 
    : T_Naam(nieuwe_naam)
{
    cout << "calling base class BasisToestand constructor for " << T_Naam << endl;
}

BasisToestand::~BasisToestand()
{
    cout << "calling base class BasisToestand destructor for " << T_Naam << endl;
}

const string BasisToestand::getName () const 
{
    return T_Naam;
}

//Derived class header:

#ifndef T_Tsunami_H // preprocessor wrapper
#define T_Tsunami_H

#include <string>
using std::string;

//#include "BasisToestand.h" // base class header

const static double PI = 3.1415926535897932384626433832795;

class T_Tsunami : public BasisToestand
{

public:

    // Constructor with default arguments
    T_Tsunami (const double norm = 1., const double mean = 0., 
           const double sigma = 1., const string="T_Tsunami");

    ~T_Tsunami(); // destructor

    // Set Functions
    void setNorm( const double norm = 1. );
    void setMean( const double mean = 0. );
    void setSigma( const double sigma = 1. );

    // Get Functions are all declared const
    const double getNorm() const;
    const double getMean() const;
    const double getSigma() const;

    virtual const double getVal(double) const;            //THIS WORKS
//virtual const vector<double> Toestand(int) const;   //PROBLEM

// Overloaded operators is also declared const
virtual const double operator()(double = 0.) const;   //THIS WORKS

private:

    double p0;
    double p1;
    double p2;

};

#endif


//Derived class .cpp

#include <iostream>
using std::cout;
using std::endl;

#include <cmath>

//#include "T_Tsunami.h" // Only T_Tsunami header file needed

T_Tsunami::T_Tsunami (const double norm, const double mean, 
           const double sigma, const string nieuwe_naam)  
      : BasisToestand(nieuwe_naam),
      p0(norm),
      p1(mean),
      p2(sigma)
{
    cout << "calling derived class T_Tsunami constructor for " << getName() << endl;
}

T_Tsunami::~T_Tsunami()
{
    cout << "calling derived class T_Tsunami destructor for " << getName() << endl;
}

const double T_Tsunami::getVal(double x) const
{
    return p0/p2/(sqrt(2*PI))*exp(-pow((x-p1),2)/(2*pow(p2,2)));
}

const double T_Tsunami::operator()(double x) const    // overloaded () operator WORKS
{
    return getVal(x);
}

void T_Tsunami::setNorm (const double norm)
{
    p0 = norm;
}
void T_Tsunami::setMean (const double mean)
{
    p1 = mean;
}
void T_Tsunami::setSigma (const double sigma)
{
    p2 = sigma;
}
const double T_Tsunami::getNorm() const
{
    return p0;
}
const double T_Tsunami::getMean() const
{
    return p1;
}
const double T_Tsunami::getSigma() const 
{
    return p2;
}


//THIS IS WHAT MY VIRTUAL FUNCTION "TOESTAND" SHOULD DO FOR THIS DERIVED CLASS
const vector<double> BasisToestand::Toestand(int GOLF) const            
{                           
    vector<double>T_1;
    for( int i = 0; i < GOLF; i++ )
        {   double y = 0.25*(1-tanh(double(i-75)/5));
            T_1.push_back(y);
        }
    cout<< "Creating vector T_1" << endl;
    return T_1;
}


//Main function:

#include <iostream>
using std::cout;
using std::endl;
using std::scientific;

#include <string>
using std::string;

#include <cmath>

#include <iomanip>
using std::setw;
using std::setprecision;

#include <vector>
using std::vector;


//#include "BasisToestand.h"
//#include "T_Tsunami.h"


int main()
{

    T_Tsunami myTsunami_1;
    BasisToestand *funPtr1 = &myTsunami_1;
    BasisToestand& funRef1 = myTsunami_1;

    cout << "value at x=0 using pointers is " << funPtr1->getVal(0.) << endl;  //WORKS
    cout << "value at x=0 using references is " << funRef1(0.) << endl;        //WORKS

    cout << "Testing Tsunami" << funPtr1->Toestand(10) << endl;       

    //THIS DOES NOT WORK, the bold thing is where I get the error.

    return 0;
 }