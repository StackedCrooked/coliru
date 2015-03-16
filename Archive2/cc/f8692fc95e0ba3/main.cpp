#include <cstdlib>
#include <iostream>

using namespace std;

struct dati_anagrafici
{
char nome[100];
char cognome[100];
char sesso;
char luogo[100];
int giorno;
int mese;
int anno;
char indirizzo [30];

};

int main(int argc, char *argv[])
{
dati_anagrafici persona;
cout<<"Dati anagrafici\n";
cout<<"Cognome: ";
cin.getline(persona.cognome,100);
cout<<"Nome: ";
cin.getline(persona.nome,100);
cout<<"Indirizzo: ";
cin>>persona.indirizzo;
cout<<"Sesso (m/f): ";
cin>>persona.sesso;
cout<<"Luogo di nascita: ";
cin>>persona.luogo;
cout<<"Giorno Mese Anno di nascita: ";
cin>>persona.giorno;
cin>>persona.mese;
cin>>persona.anno;
cout<<"\nRIEPILOGO DATI:\n";
cout<<persona.nome<<" "<<persona.cognome<<" ";
cout<<"residente in";

cout<<"nat";
if (persona.sesso=='m')
cout<<"o";
else
cout<<"a";
cout<<" a "<<persona.luogo;
cout<<" il "<<persona.giorno<<"/"<<persona.mese<<"/"<<persona.anno<<"\n";

system("PAUSE");
return EXIT_SUCCESS;
}