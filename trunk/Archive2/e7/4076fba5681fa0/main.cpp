#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

struct Faktura
{
    int id;
	int castka;
};

class Faktury
{
private:
	bool jePripojeny;
	int pocetFaktur;
	vector<Faktura> faktury;
public:
	Faktury() : jePripojeny{ false }, pocetFaktur{ 0 }
	{
		this->jePripojeny = true;
		cout << "Uspesne jsem vytvoril pripojeni k serveru :)" << endl;
	}

	~Faktury()
	{
		cout << "Faktury budou uvolneny z pameti, zkontroluju radsi, zda je pripojeni uzavreno ;)";
		ZavritPripojeni();
	}

	int PocetFaktur()
	{
		return this->pocetFaktur;
	}

	void PridejFakturu(Faktura faktura)
	{
		this->faktury.push_back(faktura);
	}

	void ZmenFakturu(int index, Faktura novaFaktura)
	{
		if ( (index < 0) ||  (index >= this->pocetFaktur))
		{
			throw out_of_range("Neplatný index faktury");
		}

		this->faktury[index] = novaFaktura;
	}

	bool ZkusUlozitFakturu()
	{
        return true;
	}

	void ZavritPripojeni()
	{
		if (this->jePripojeny == true)
		{
			this->jePripojeny = false;
			cout << "Ukoncil jsem pripojeni k serveru :)" << endl;
		}
		else
		{
			cout << "Pripojeni neni aktivni, takze ho nemusim zavirat ;)" << endl;
		}
	}
};


int main()
{
	try
	{
		Faktury faktury; // automaticky na zasobniku
		faktury.PridejFakturu(Faktura{ 1, 100 });
		faktury.PridejFakturu(Faktura{ 2, 300 });
		faktury.PridejFakturu(Faktura{ 3, 400 });
		faktury.ZmenFakturu(2, Faktura{ 2, 200 });
		faktury.ZmenFakturu(5, Faktura{ 2, 200 });
		faktury.PridejFakturu(Faktura{ 3, 400 });
		// odeslat email atd.
		faktury.ZavritPripojeni();
	}
	catch (out_of_range& error)
	{
		cout << error.what();
	}
	catch (bad_alloc& error)
	{

	}

	return 0;
}

