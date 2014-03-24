#include <iostream>

using namespace std;

class Matice
{
private:
    int* p;
	int m;
	int n;
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
}

int main()
{
	Matice matice(2, 3);
	matice.NastavPrvek(1, 1, 10);
	Vypis(matice);
	return 0;
}