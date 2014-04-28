#include <iostream>
#include <string>
#include <vector>

//ganze Zahlen
char charnumber;
short shortnumber;
int integernumber;
long longnumber;
long long longlongnumber;

//Gleitkommazahlen
float floatnumber;
double doublenumber;
long double longdoublenumber;

//Buchstaben
char charbuchstabe;

//Wahrheitswerte
bool boolean;


//Vielleicht selber mal ausloggen, wenn man nicht will, dass jemand anders einfach Kommentare schreibt.... :D
int main()
{
    std::cout << "Ohne Initialisierung" << "\n"
    << "Ganze Zahlen" << "\n"
    << "char: " << charnumber << "\n"
    << "short: " << shortnumber << "\n"
    << "int: " << integernumber << "\n"
    << "long: " << longnumber << "\n"
    << "long long: " << longlongnumber << "\n"
    << "Gleitkommazahlen" << "\n"
    << "float: " << floatnumber << "\n"
    << "double: " << doublenumber << "\n"
    << "long double: " << longdoublenumber << "\n"
    << "Buchstaben" << "\n"
    << "char: " << charbuchstabe << "\n"
    << "Wahrheitswerte" << "\n"
    << "bool: " << boolean << "\n" << "\n";
    
    charnumber=1;
    shortnumber=1;
    integernumber=1;
    longnumber=1;
    longlongnumber=1;
    floatnumber=1.5f;
    doublenumber=1.5;
    longdoublenumber=1.5;
    charbuchstabe = 'a';
    boolean=true;
    
    std::cout << "Mit Initialisierung" << "\n"
    << "Ganze Zahlen" << "\n"
    << "char: " << charnumber << "\n"
    << "short: " << shortnumber << "\n"
    << "int: " << integernumber << "\n"
    << "long: " << longnumber << "\n"
    << "long long: " << longlongnumber << "\n"
    << "Gleitkommazahlen" << "\n"
    << "float: " << floatnumber << "\n"
    << "double: " << doublenumber << "\n"
    << "long double: " << longdoublenumber << "\n"
    << "Buchstaben" << "\n"
    << "char: " << charbuchstabe << "\n"
    << "Wahrheitswerte" << "\n"
    << "bool: " << boolean << "\n";
}