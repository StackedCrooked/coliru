#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string a, b("foofoofoo"), c("barbarbar");
	
    std::vector<std::string> v;
    
    for (int i = 0; i < 10000; ++i)
	{
        b.resize(10+i);
	    v.push_back(b);
	}
    
	for (int count = 0; count < 5; ++count)
	{
        c.resize(10+count*10);
        
		auto begin = std::chrono::high_resolution_clock::now();
        size_t sz = 0;
		for (const auto & r : v)
		{
			a = r + c;
            sz += a.size();
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> d = end - begin;

		std::cout << "operator+ : " << d.count() << ' ' << sz << std::endl;

		begin = std::chrono::high_resolution_clock::now();
        sz = 0;
		for (const auto & r : v)
        {
			a = r;
			a += c;
            sz += a.size();
		}
		end = std::chrono::high_resolution_clock::now();
		d = end - begin;
	
		std::cout << "operator+=: " << d.count() << ' ' << sz << std::endl << std::endl;
	}

	return 0;
}