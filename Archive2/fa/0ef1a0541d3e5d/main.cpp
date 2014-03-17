#include <iostream>

using namespace std;

int main()
{
    int Zahl1 = 5, Zahl2 = 3;
    float Quotient;
    
    cout << "Bitte geben Sie nun die erforderlichen Zahlenwerte ein.\n"
         << "Zahl 1: ";
    cin >> Zahl1;
    cout << "Zahl 2: ";
    cin >> Zahl2;
    
    Quotient = Zahl1 / Zahl2;
    cout << "\nOhne explizites Casting beträgt der Quotient: " << Quotient;
    
    Quotient = static_cast<float>(Zahl1 / Zahl2);
    cout << "\nMit explizitem Casting (in Klammern) beträgt der Quotient: " << Quotient;
    
    Quotient = static_cast<float>(Zahl1) / Zahl2;
    cout << "\nMit explizitem Casting (eine Variable) beträgt der Quotient: " << Quotient << endl;
    
    
    
}
