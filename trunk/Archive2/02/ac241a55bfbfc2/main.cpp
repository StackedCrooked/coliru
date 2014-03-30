#include <iostream>

using namespace std;

class Matice
{
private:
    int* p;
	int m;
	int n;

	// opakem hluboke kopie (deep copy) je melka kopie (shallow copy)
	void UdelejHlubokouKopii(const Matice& original)
	{
		int pocetPrvku = this->m * this->n;
		this->p = new int[pocetPrvku];
		for (int i = 0; i < pocetPrvku; ++i)
		{
			this->p[i] = original.p[i];
		}
	}

public:
	Matice(int m, int n) : m{ m }, n{ n }
	{
		int pocetPrvku = this->m * this->n;
		this->p = new int[pocetPrvku];
		for (int i = 0; i < pocetPrvku; ++i)
		{
			this->p[i] = 0;
		}
	}

	// kopirovaci konstruktor
	Matice(const Matice& original) : p{ nullptr }, m{ original.m }, n{ original.n }
	{
		this->UdelejHlubokouKopii(original);
	}
	// Pokud trida potrebuje destruktor,
	// tak je velka pravdepodobnost, ze
	// potrebuje i kopirovaci konstruktor
	// a pretizeny operator prirazeni
	~Matice()
	{
		if (this->p != nullptr)
		{
			delete[] this->p;
		}
	}

	// pretizeny operator prirazeni
	Matice& operator = (const Matice& original)
	{
		// mohl bych udelat i optimalizaci a pokud
		// by mel original stejne rozmery, tak bych "zrecyklovat" puvodni data

		if (this->p != nullptr)
		{
			delete[] this->p;
		}

		this->m = original.m;
		this->n = original.n;
		this->UdelejHlubokouKopii(original);

		return *this;
	}

	void NastavPrvek(int i, int j, int hodnota)
	{
		int index = (i * n) + j;
		this->p[index] = hodnota;
	}

	int VratPrvek(int i, int j) const
	{
		int index = (i * n) + j;
		int hodnota = this->p[index];
		return hodnota;
	}

	int VratPocetRadku() const
	{
		return this->m;
	}

	int VratPocetSloupcu() const
	{
		return this->n;
	}

};

void Vypis(const Matice& matice)
{
	cout << "pocet radku = " << matice.VratPocetRadku() << endl;
	cout << "pocet sloupcu = " << matice.VratPocetSloupcu() << endl;
	for (int i = 0; i < matice.VratPocetRadku(); ++i)
	{
		for (int j = 0; j < matice.VratPocetSloupcu(); ++j)
		{
			int hodnotaPrvku = matice.VratPrvek(i, j);
			cout << hodnotaPrvku << " ";
		}
		cout << endl;
	}

	cout << endl;
}

int main()
{
	Matice matice(2, 3);
	matice.NastavPrvek(1, 1, 10);
	
	Matice kopie1(matice);	// prima inicializace
	kopie1.NastavPrvek(0, 0, 1);

	Matice kopie2 = matice; // incializace 
	kopie2.NastavPrvek(0, 1, 2);

	Matice matice2(2, 2);
	matice2 = matice; // prirazeni hodnoty
	matice2.NastavPrvek(0, 2, 3);

	Vypis(matice);
	Vypis(kopie1);
	Vypis(kopie2);
	Vypis(matice2);
	return 0;
}