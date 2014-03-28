#include <iostream>

using namespace std;

class Matice
{
private:
    int* p;
	int m;
	int n;

	// deep copy (opak je melka kopie, shallow copy)
	void UdelejHlubokouKopii(const Matice& original)
	{
		this->m = original.m;
		this->n = original.n;

		int pocetPrvku = this->m * this->n;
		this->p = new int[pocetPrvku];
		for (int i = 0; i < pocetPrvku; ++i)
		{
			this->p[i] = original.p[i];
		}
	}

public:
	Matice(int m, int n) : p{ nullptr }, m{ m }, n{ n }
	{
		int pocetPrvku = this->m * this->n;
		this->p = new int[pocetPrvku];
		for (int i = 0; i < pocetPrvku; ++i)
		{
			this->p[i] = 0;
		}
	}

	Matice(const Matice& original) : p{ nullptr }, m{ 0 }, n{ 0 }
	{
		this->UdelejHlubokouKopii(original);
	}

	// pretizeny operator prirazeni
	Matice& operator = (const Matice& original)
	{
        // uvolnim puvodni data
    	if (this->p != nullptr)
		{
			delete[] this->p;
		}
        
        // alokuju nove data a zkopiruju hodnoty
		this->UdelejHlubokouKopii(original);
		return *this;
	}

	~Matice()
	{
		if (this->p != nullptr)
		{
			delete[] this->p;
		}
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
	matice.NastavPrvek(1, 1, 1);
	
	Matice kopie = matice; // inicialializace, vola se kopirovaci konstruktor
    kopie.NastavPrvek(1, 1, 2);


	Matice kopie2(4, 4);
	kopie2 = matice; // operator prirazeni =
    kopie2.NastavPrvek(1, 1, 3);
    
    Vypis(matice);
    Vypis(kopie);
    Vypis(kopie2);
    
	return 0;
}