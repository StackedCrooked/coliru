#include <iostream>
#include <vector>
#include <cstring>
#include <string>

int main()
{
    std::vector<double> vec;
	std::string str = "5, 4.2, 55, 47,4.,89.0, 7";
	for (auto ptr = str.data();; ++ptr)
	{
		char* end;
		double d = std::strtod(ptr, &end);

		if (end == ptr)
			break;

		vec.push_back(d);

		if (!(ptr = std::strchr( end, ',' )))
			break;
	}

	for (auto d : vec)
		std::cout << d << " ";
}
