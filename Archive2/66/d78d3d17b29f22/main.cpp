#include <iostream>
#include <vector>

#include <string>
#include <fstream>

using namespace std;

class TKsiazka
{
    string autor;
	string tytul;
	double cena; // wartosci pieniezne nie powinny byc zmiennoprzecinkowe
				 // to powinna byc int liczba groszy (lub ulamkow grosza)

public:

	TKsiazka() : cena(0) {}

	TKsiazka(string const& a, string const& t, double c):
		autor(a), tytul(t), cena(c) {}

	string const& getAutor() const { return autor; }
	string const& getTytul() const { return tytul; }
	double getCena() const { return cena; }

	friend ostream& operator<<(ostream&, TKsiazka const&);
	friend istream& operator>>(istream&, TKsiazka&);
};

ostream& operator<<(ostream& o, TKsiazka const& k){
	o << k.autor << " " << k.tytul << " " << k.cena;
	return o;
}

istream& operator>>(istream& i, TKsiazka& k){
	i >> k.autor >> k.tytul >> k.cena;
	return i;
}

class TTablicaKsiazek
{
	vector<TKsiazka> dane;
public:
	TTablicaKsiazek(size_t n){
		dane.reserve(n);
	}

	void usun(size_t index){
		dane.erase(dane.begin()+index);
	}

	size_t iloscKsiazek() const {
		return dane.size();
	}

	TKsiazka const& operator[](size_t n) const {
		return dane[n];
	}

	TKsiazka& operator[](size_t n){
		return dane[n];
	}

	TTablicaKsiazek& operator<<(TKsiazka const& k){
		dane.push_back(k);
		return *this;
	}
};

ostream& operator<<(ostream& o, TTablicaKsiazek const& ttk){
	for(size_t i = 0; i < ttk.iloscKsiazek(); i++){
		o << ttk[i] << endl;
	}
	return o;
}

void doPliku(string const& plik, TTablicaKsiazek const& ttk){
	fstream f(plik.c_str(),ios::out);

	if(!f) return;

	f << ttk;

	f.close();
}

void zPliku(string const& plik, TTablicaKsiazek& ttk){
	fstream f(plik.c_str(),ios::in);
	TKsiazka k;
	while(f >> k){
		ttk << k;
	}
	f.close();
}

void wypiszWykaz(TTablicaKsiazek const& ttk){
	cout << ttk;
}

void wyswietlNajtanszaKsiazke(TTablicaKsiazek const& ttk){
	TKsiazka const* najtansza = 0;
	for(size_t i = 0; i < ttk.iloscKsiazek(); i++){
		if(!najtansza || najtansza->getCena() > ttk[i].getCena()){
			najtansza = &ttk[i];
		}
	}
	if(najtansza){
		cout << najtansza->getTytul() << endl;
	}
}

int main()
{
	TKsiazka k1("Grey","50_twarzy",13.37), k2("J.K._Rowling", "Chary_Poter", 69);
	TTablicaKsiazek tk(10);
	tk << k1 << k2;
	cout << tk[0] << endl;
//	tk.usun(0);
	cout << tk[0] << endl;
	doPliku("test.txt",tk);

	TTablicaKsiazek tk2(10);
	zPliku("test.txt",tk2);
	wypiszWykaz(tk2);
	wyswietlNajtanszaKsiazke(tk2);
	return 0;
}

