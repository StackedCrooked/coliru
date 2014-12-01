    #include <iostream>
    #include <string.h>
    using namespace std;
     
    int main() {
    int rozmiar = 1000;
    char tekst[rozmiar];
    cout << "Podaj tekst do odwrócenia:" <<endl;
    cin.getline(tekst, rozmiar);
    rozmiar = strlen(tekst);
     
    for(int i=0; i<=rozmiar; i++) {
    cout<<tekst[rozmiar-1-i];
    }
    cout<<endl;
     
    }