#include <iostream>
#include "Sales_item.h"
 
struct Sales_data
{
    std::string bookNo;
	unsigned units_sold;
	double revenue;
};
 
int main()
{
	////////////////////////////////////////////////////////////
	// Exercise 7.1 (Books Version)
	////////////////////////////////////////////////////////////
 
	Sales_item total;
	if (std::cin >> total)
	{
		Sales_item trans;
		while (std::cin >> trans)
		{
			if (total.isbn() == trans.isbn())
				total += trans;
			else
			{
				std::cout << total << std::endl;
				total = trans;
			}
		}
		std::cout << total << std::endl;
	}
	else
	{
		std::cerr << "No data?" << std::endl;
		return -1;
	}
 
	////////////////////////////////////////////////////////////
	// Exercise 7.1 (My Version)
	////////////////////////////////////////////////////////////
 
	Sales_data total;
}