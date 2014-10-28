#include <iostream>
#include <vector>
#include <stdint.h>
#include <iterator>

int main()
{
    float data[] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.1};

	std::vector<uint8_t> result;
	result.push_back(77.1);
	result.push_back(77.2);
	result.push_back(77.3);

	result.reserve(10+3);
	result.resize(10+3);

	std::copy(data, data + 10, std::back_inserter(result));

	for (unsigned int i = 0; i < result.size(); i++)
	{
		std::cout << (unsigned int)result[i] << " ";
	}
}