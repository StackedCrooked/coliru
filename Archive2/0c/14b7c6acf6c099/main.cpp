#include <iostream>
#include <cassert>

using namespace std;

int Berechnung (int x , int y)

{
    assert(x>=0);
    assert(y>=0);

    return  (x<250) ? (y<100) ? 10 : (y<300) ? 15 : 20 :(y<200) ? 25 : (y<400) ? 35 : 45;
}



int main()
{
    cout<<"Willkommen bei ihrem Tarifmanager Version 1.0" <<endl;
    float x; cout << "Eingabe Anzahl der gewünschten SMS für deinen Tarif" << endl;
    cin >> x;
    (x!=(int)x) ? cout<< "Fehler: Bitte geben Sie eine ganze Anzahl an SMS ein,starten Sie das Programm erneut" <<endl :
    (x<0) ? cout<<"Fehler: Bitte geben Sie eine positive SMS Anzahl ein,starten Sie das Programm erneut" <<endl : cout << "Eingabe Korrekt" <<endl;
    float y; cout <<" Eingabe der gewünschten Gesprächsminuten für deinen Tarif"<< endl;
    cin >> y;
    (y!=(int)y) ? cout<< "Fehler: Bitte geben Sie eine ganze Anzahl an Gesprächsminuten ein,starten Sie das Programm erneut" <<endl :
    (y<0) ? cout<<"Fehler: Bitte geben Sie eine positive Gesprächsminutenanzahl ein,starten Sie das Programm erneut" <<endl : cout << "Eingabe Korrekt" <<endl;

    cout <<"Ihr Betrag Ihn Euro für die gemachten Eingaben:" <<endl;
    (x!=(int)x) ? cout <<"Fehler" <<endl :  (y!=(int)y) ? cout<< "Fehler" <<endl : cout <<Berechnung (x,y)  <<endl;
    return 0;


}