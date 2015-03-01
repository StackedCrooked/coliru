#include <iostream>
#include <iterator>

int main()
{
    int my_int = 12345;
	int my_int_array[5];

	while (my_int > 0)
	{
   	 	int digit = my_int % 10;
    	my_int /= 10;

    	std::cout << digit << std::endl;
	}

}