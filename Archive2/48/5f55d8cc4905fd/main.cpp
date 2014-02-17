#include <stdexcept>
#include <iostream>
#include <memory>

using namespace std;

class Robot
{
private:
    double rychlost;
public:
	Robot() : rychlost{ 0 }
	{
		cout << "Vse je pripraveno, muzeme vyjet :)" << endl;
	}

	double VratMaximalniRychlost()
	{
		return 10;
	}

	void NastavRychlost(double rychlost)
	{
		if (rychlost >= this->VratMaximalniRychlost())
		{
			cout << "Tato rychlost by mne asi rozbila :( " << this->rychlost << "km/h" << endl;
			throw std::length_error("Error 100: Prekrocena maximalni rychlost!");
		}
		
		this->rychlost = rychlost;
		cout << "Jedu rychlosti: " << this->rychlost << "km/h" << endl;
	}

	void Zastav()
	{
		this->rychlost = 0;
		cout << "Bezpecne jsem robota zastavil :)" << endl;
	}

	~Robot()
	{
		cout << "Obsluha robota byla ukoncena, otestuji zda je zastaveny." << endl;
		if (this->rychlost > 0)
		{
			cout << "Zjistil jsem, ze robot porad jede, pokusim se ho bezpecne zastavit ;)" << std::endl;
			Zastav();
		}
	}
};

int main()
{
	shared_ptr<Robot> robot2 = make_shared<Robot>();
	
	try
	{
		Robot robot; // automaticky
		robot.NastavRychlost(7);
		robot.NastavRychlost(8);
		double novaRychlost = 10;
        // spravny zpusob, v dobre napsanem programu je vyjimka pouze vyjimkou
		if (novaRychlost < robot.VratMaximalniRychlost())
		{
			robot.NastavRychlost(novaRychlost);
		}

		// nekdo mi omylem prepsal pamet
		robot.NastavRychlost(10);
		// pokud v bloku try dojde k vyjimce
		// tak se zacne uvolnovat zasobnik
		// a zavola se destruktor robota
	
		robot.Zastav();
	}
	catch (std::length_error& error)
	{
		cout << error.what();
	}
	
	return 0;
}

