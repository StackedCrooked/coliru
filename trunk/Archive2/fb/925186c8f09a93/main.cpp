#include <iostream>

struct Bystander
{
    Bystander()
	{
		std::cout << "Innocent Bystander appears" << std::endl;
	}
	~Bystander()
	{
		std::cout << "Innocent Bystander was shot" << std::endl;
	}
};

struct Accomplice
{
	Bystander const &b;
	Accomplice(Bystander const &b)
	: b(b)
	{
		std::cout << "Accomplice received Innocent Bystander" << std::endl;
	}
	~Accomplice()
	{
		std::cout << "Accomplice abandoned Innocent Bystander" << std::endl;
	}
};

auto Perpetrator(Bystander const &b)
-> Accomplice
{
	std::cout << "Committing a Crime by giving Innocent Bystander to Accomplice" << std::endl;
	return b;
}

int main()
{
	std::cout << "About to interact with Perpetrator" << std::endl;
	auto a = Perpetrator(Bystander());
	std::cout << "Finished interacting with Perpetrator" << std::endl;
}
