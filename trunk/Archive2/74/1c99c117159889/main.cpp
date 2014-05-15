#include <array>
#include <iostream>
#include <string>

using namespace std;

class Water
{
    private:
		std::array<std::string, 4> elements;
		std::string water;
		bool elementExists;
		int i;

	public:
		Water (std::string const & n)
		: elements	{ "Steam", "Mud", "Sea", "Rain" }
		, water		(n)
		, i			(-1)
		{}
};

int main ()
{
	Water w("");
}