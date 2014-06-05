#include <iostream>
#include <string>
#include <vector>



int main()
{
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
                    std::cout << " Cows " << iCows << std::endl;
				}
			}
		}
	}
}
