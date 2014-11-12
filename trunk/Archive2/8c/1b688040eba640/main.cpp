#include <iostream>
using namespace std;

struct Persona
{
    int eta;
    int altezza;
};

struct Gruppo
{
    Persona A;
    Persona B[3];
};

Gruppo folla = {
    {10, 11},
    {
        { 20, 21},
        { 30, 31},
        { 40, 41},
    }
};

int main()
{
    cout << "folla.A.eta = " << folla.A.eta << endl;
    cout << "folla.A.altezza = " << folla.A.altezza << endl;
    
    cout << "folla.B[0].eta = " << folla.B[0].eta << endl;
    cout << "folla.B[1].eta = " << folla.B[1].eta << endl;
    cout << "folla.B[2].eta = " << folla.B[2].eta << endl;
}
