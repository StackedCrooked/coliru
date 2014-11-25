#include <string>
#include <fstream>
#include <iostream>
#include <vector>

bool do_it_or_dont_do_it(int counter, int version, int calcDate)
{
    if ((counter==1) || ((counter==2)&& (version!=5)) || ((counter==4)&& (version<=2)))
		return true;
	if ((counter==3) && (calcDate>=40238) && (version==2))
		return true;
	if ((version>=3) && (counter>=3) && !((version==5) && (counter==6)) )
		return true;
        
    return false;
}

void show_grid(int calc_date)
{
    std::cout << "v\\c   1 2 3 4 5 6 7\n" << std::endl; 
    for(int version = 1; version <= 7; ++version)
    {
        std::cout << version << "     ";
        for(int counter = 1; counter <= 7; ++counter)
        {
            std::cout << do_it_or_dont_do_it(counter, version, calc_date) << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::cout << "calc_date = 40200" << std::endl;
    show_grid(40200);
    
    std::cout << "\n\ncalc_date = 42200" << std::endl;
    show_grid(42200);
}