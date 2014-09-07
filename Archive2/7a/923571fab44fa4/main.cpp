 #include <iostream>
#include <math.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
 
 
 
int main(int argc, char** argv) 
{
    int a=0;
    float suma=0, b=0;                    // zmienne 
 
    /********************************************************************************/
    cout << "Wprowadz liczbe elementow (Max 10) --> ";        
    cin >> a;
    float tablica[a];                                            // wielkosc tablicy
    if (a<=10)
    {    
    /***************************************************************************************/
    cout << "\n\nWprowadz teraz kolejne liczby do tablicy";    
    for (int i=0;i<a;i++)
    {
    cout << "\nElement " << i+1 << " --> ";                            // wprowadzanie elementow
    cin >> b;
    tablica[i]=b;
    }
/***************************************************************************************************/    
 
    //**Jak dokonczyc tu ten kod aby OBLICZYŁ iloczyn, iloraz i różnice, wczytanych elementow i nastepnie wypisal wartosc. I to wszystko chcialbym miec w osobnych programach tzn, osobno iloczyn itd..**//foo//
 
}
 
return 0;
}