#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template < class Typ > class cMenu
{
public:
   
    struct sDane //STRUKTURA DO PRZECHOWYWANIA NAZWY I FUNKCJI W MENU
    {
        string Nazwa;
        function < Typ > funkcja; //function BEDZIE PRZECHOWYWAC ADRES FUNKCJI
    } Dane;
   
    bool wypisz(); //FUNKCJA WYPISUJACA MENU
   
    void Dodaj()
    {
        vecWypis.push_back( Dane );
    }
   
    //KONSTRUKTOR
    cMenu()
        : pozycja( 0 )
        , prawda( true )
    { };
   
private:
   
    int pozycja; //ZMIENNA DO WYBRANIA ODPOWIEDNIEJ FUNKCJI
    bool prawda; //ZMIENNA DO WYJSCIA Z PETLI WYPISUJACEJ
   
    vector < sDane > vecWypis; //vector PRZECHOWUJACY DANE ZE STRUKTURY
};

void Gra() { }
void Lab() { }

int main()
{
   //TWORZYMY OBIEKT cMenu KTORY PRZECHOWUJE FUNKCJE void(void)
    cMenu < void() > Menu0; //wpisywalem rozniez <void(void)> oraz <void()>
    //DODAJEMY DANE
    //1 EXIT
    Menu0.Dane.Nazwa = "EXIT";
    Menu0.Dodaj();
   
    //2 KOLKO I KRZYZYK
    Menu0.Dane.Nazwa = "KOLKO I KRZYZYK";
    Menu0.Dane.funkcja = Gra;
    Menu0.Dodaj();
   
    //3 LABIRYNT
    Menu0.Dane.Nazwa = "LABIRYNT";
    Menu0.Dane.funkcja = Lab;
    Menu0.Dodaj();
    cout << "OK\n";
}
