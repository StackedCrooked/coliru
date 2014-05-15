#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string a, b("foofoofoo"), c("barbarbar");
	
    std::vector<std::string> v;
    
    for (int i = 0; i < 1000000; ++i)
	{
	    v.push_back(b);
	}
    
    std::string::size_type sum = 0;
    
	for (int count = 0; count < 5; ++count)
	{
        sum = 0;
		auto begin = std::chrono::high_resolution_clock::now();
		for (const auto & r : v)
		{
			a = r + c;
            sum += a.length();
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> d = end - begin;

		std::cout << "sum: " << sum << "operator+: " << d.count() << std::endl;

        sum = 0;
		begin = std::chrono::high_resolution_clock::now();
		for (const auto & r : v)
        {
			a = r;
			a += c;
            sum += a.length();
		}
		end = std::chrono::high_resolution_clock::now();
		d = end - begin;
	
		std::cout << "sum: " << sum << "operator+=: " << d.count() << std::endl;
	}

	return 0;
}