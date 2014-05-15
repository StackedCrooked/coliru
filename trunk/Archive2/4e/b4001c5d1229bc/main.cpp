#include <iostream>
#include <chrono>
#include <string>
#include <iostream>


int main() {
    std::string a, b("foofoofoo"), c("barbarbar");
		
	for (int count = 0; count < 10; ++count)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100000; ++i)
		{
            b.resize(10+i);
			a = b + c;
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> d = end - begin;

		std::cout << "operator+: " << d.count() << std::endl;

		begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100000; ++i)
		{
            b.resize(10+i);
			a = b;
			a += c;
		}
		end = std::chrono::high_resolution_clock::now();
		d = end - begin;
	
		std::cout << "operator+=: " << d.count() << std::endl;
	}

	return 0;
}