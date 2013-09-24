#include <iostream>
#include <stdexcept>
using namespace std;

int main() try
{
    throw std::invalid_argument("Hello");
}
catch (const std::exception& e)
{
	std::cout << e.what() << "bla" << '\n';
}