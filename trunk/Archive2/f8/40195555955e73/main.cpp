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


int main()
{
    std::cout << "Ohne Initialisierung" << "\n"
    << "Ganze Zahlen" << "\n"
    << "char: " << charnumber << ", Groesse: " << sizeof(charnumber) << "\n"
    << "short: " << shortnumber << ", Groesse: " << sizeof(shortnumber) << "\n"
    << "int: " << integernumber << ", Groesse: " << sizeof(integernumber) << "\n"
    << "long: " << longnumber << ", Groesse: " << sizeof(longnumber) << "\n"
    << "long long: " << longlongnumber << ", Groesse: " << sizeof(longlongnumber) << "\n"
    << "Gleitkommazahlen" << "\n"
    << "float: " << floatnumber << ", Groesse: " << sizeof(floatnumber) << "\n"
    << "double: " << doublenumber << ", Groesse: " << sizeof(doublenumber) << "\n"
    << "long double: " << longdoublenumber << ", Groesse: " << sizeof(longdoublenumber) << "\n"
    << "Buchstaben" << "\n"
    << "char: " << charbuchstabe << ", Groesse: " << sizeof(charbuchstabe) << "\n"
    << "Wahrheitswerte" << "\n"
    << "bool: " << boolean << ", Groesse: " << sizeof(boolean) << "\n \n";
    
    charnumber=1;
    shortnumber=1;
    integernumber=1;
    longnumber=1;
    /* longlongnumber=1;
    floatnumber=1.5f;*/
    doublenumber=1.5;
    longdoublenumber=1.5;
    charbuchstabe = 'a';
    boolean=true;
    
    std::cout << "Mit Initialisierung" << "\n"
    << "Ganze Zahlen" << "\n"
    << "char: " << charnumber << ", Groesse: " << sizeof(charnumber) << "\n"
    << "short: " << shortnumber << ", Groesse: " << sizeof(shortnumber) << "\n"
    << "int: " << integernumber << ", Groesse: " << sizeof(integernumber) << "\n"
    << "long: " << longnumber << ", Groesse: " << sizeof(longnumber) << "\n"
    << "long long: " << longlongnumber << ", Groesse: " << sizeof(longlongnumber) << "\n"
    << "Gleitkommazahlen" << "\n"
    << "float: " << floatnumber << ", Groesse: " << sizeof(floatnumber) << "\n"
    << "double: " << doublenumber << ", Groesse: " << sizeof(doublenumber) << "\n"
    << "long double: " << longdoublenumber << ", Groesse: " << sizeof(longdoublenumber) << "\n"
    << "Buchstaben" << "\n"
    << "char: " << charbuchstabe << ", Groesse: " << sizeof(charbuchstabe) << "\n"
    << "Wahrheitswerte" << "\n"
    << "bool: " << boolean << ", Groesse: " << sizeof(boolean) << "\n";
}