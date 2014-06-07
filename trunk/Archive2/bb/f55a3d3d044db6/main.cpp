#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

bool CreateTestFile(const char* fileName, uint32_t cookieValue, uint32_t numItems)
{
    std::cout << "Creating test file...\n";
	std::ofstream f(fileName, std::ios::binary);
	if(f)
	{
		const size_t cookiePos = (rand() / static_cast<double>(RAND_MAX)) * (numItems - 1);
		std::vector<uint32_t> v(numItems);
		for(size_t i = 0; i < v.size(); ++i)
		{
			uint32_t val = rand();
			v[i] = val != cookieValue ? val : 0;
		}
		v[cookiePos] = cookieValue;
		if(f.write(reinterpret_cast<char*>(&v[0]), v.size() * sizeof(uint32_t)))
		{
			std::cout << "Cookie '" << cookieValue << "' written at position " << cookiePos << "\n";
			return true;
		}
	}
	std::cout << "Error creating test file\n";
	return false;
}

int FindValue(const char* fileName, uint32_t cookieValue)
{
	std::cout << "Finding value...\n";
	std::ifstream f(fileName, std::ios::binary | std::ios::ate);
	if(f)
	{
		const size_t fileSize = f.tellg();
		f.seekg(0, std::ios::beg);
		std::vector<uint32_t> v((fileSize / 4) + (fileSize % 4 == 0 ? 0 : 1));
		if(f.read(reinterpret_cast<char*>(&v[0]), fileSize))
		{
			for(size_t i = 0; i < v.size(); ++i)
			{
				if(v[i] == cookieValue)
				{
					std::cout << "Found Cookie '" << cookieValue << "' at position " << i << "\n";
					return i;
				}
			}
		}
	}
	std::cout << "Cookie not found\n";
	return -1;
}

int main()
{
	std::srand(std::time(0));

	const uint32_t cookieValue = 0xff000000;
	const uint32_t numItems = 1024 * 256; //1MB
	const char* fileName = "test.bin";

	if(CreateTestFile(fileName, cookieValue, numItems))
	{
        FindValue(fileName, cookieValue);
	}
	return 0;
}

