#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    // std::vector<std::string> words = {
    //    "Hello", "from", "GCC", __VERSION__, "!"
    // };
    // std::cout << words << std::endl;
    // Chooks = 5 for $1
    // Sheep = 1 for $1
    // Cows = 1 for $5
    for (int iCows=1;iCows<99;iCows++)
    {
    	for (int iSheep=1;iSheep<99;iSheep++)
		{
			for (int iChooks=1;iChooks<99;iChooks++)
			{
				if (iChooks+iSheep+iCows==100&&iChooks*0.2+iSheep*1+iCows*10==100)
				{
					std::cout << " Chooks " << iChooks;
                    std::cout << " Sheep " << iSheep;
                    std::cout << " Cows " << iCows;
				}
			}
		}
	}
}
