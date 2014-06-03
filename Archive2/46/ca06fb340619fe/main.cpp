#include<iostream>
double dodawanie( double x, double y );
double odejmowanie( double x, double y );
double dzielenie( double x, double y );
double mnozenie( double x, double y );
double calculate( double x, double y, double( * wsk_na_funkcje )( double, double ) );

int main()
{
    using namespace std;
    double liczba1, liczba2, wynik;
    double( * dzialania[ 4 ] )( double, double ) = { dodawanie, odejmowanie, dzielenie, mnozenie };
    double( ** wsk )( double, double ) = dzialania; // wskaznik do adresu pierwszego elementu tablicy wskaznikow funkcji dzialania
   
    do
    {
        cout << "Podaj pare liczb. Jesli chcesz zakonczyc wcisnij x.\n";
        cin >> liczba1 >> liczba2;
       
        for( int i = 0; i < 4; i++ )
        {
            wynik = calculate( liczba1, liczba2, wsk[ i ] ); //ERROR
            cout << wynik << endl;
           
        }
       
    } while( cin );
   
    return 0;
   
}

double dodawanie( double x, double y )
{
    return x + y;
}

double odejmowanie( double x, double y )
{
    return x - y;
}

double dzielenie( double x, double y )
{
    return x / y;
}

double mnozenie( double x, double y )
{
    return x * y;
}

double calculate( double x, double y, double( * wsk_na_funkcje )( double, double ) )
{
    return( * wsk_na_funkcje )( x, y );
}