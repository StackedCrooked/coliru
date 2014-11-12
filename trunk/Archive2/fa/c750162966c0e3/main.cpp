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

Gruppo folla[3] = {
    {
        {10, 11},
            {
                { 20, 21},
                { 30, 31},
                { 40, 41},
            }
    },
    
    {
        {100, 101},
            {
                { 200, 201},
                { 300, 301},
                { 400, 401},
            }
    },
    
    {
        {1000, 1001},
            {
                { 2000, 2001},
                { 3000, 3001},
                { 4000, 4001},
            }
    }
};

int main()
{
    cout << "folla.A.eta = " << folla[0].A.eta << endl;
    cout << "folla.A.altezza = " << folla[0].A.altezza << endl;
    
    cout << "folla.B[0].eta = " << folla[0].B[0].eta << endl;
    cout << "folla.B[1].eta = " << folla[0].B[1].eta << endl;
    cout << "folla.B[2].eta = " << folla[0].B[2].eta << endl;
    
    cout << "folla[1].B[0].eta = " << folla[1].B[0].eta << endl;
    cout << "folla[1].B[1].eta = " << folla[1].B[1].eta << endl;
    cout << "folla[1].B[2].eta = " << folla[1].B[2].eta << endl;
    
    cout << "folla[2].B[0].eta = " << folla[2].B[0].eta << endl;
    cout << "folla[2].B[1].eta = " << folla[2].B[1].eta << endl;
    cout << "folla[2].B[2].eta = " << folla[2].B[2].eta << endl;
}
