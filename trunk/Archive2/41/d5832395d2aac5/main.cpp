#include <vector>
#include <algorithm>
#include <iostream>

    
	void TestFunc_for_each()
	{
		std::vector<long> aSource(10);
		std::vector<long> aTarget;

		std::generate(aSource.begin(), 
					  aSource.end(),
					  [](){
			static long counter = 0;
			++counter;
			return counter;
		});

		aTarget.reserve(aSource.size());

		for_each(aSource.begin(), aSource.end(), [&aTarget](long source) { aTarget.emplace_back(source + 1); });

		//std::cout << "Source:" << std::endl;
		//for_each(aSource.cbegin(), aSource.cend(), [](long source) { std::cout << source << std::endl; });
		std::cout << "Target:" << std::endl;
		for_each(aTarget.cbegin(), aTarget.cend(), [](long Target) { std::cout << Target << std::endl; });

	}
	
	int main()
	{
	    TestFunc_for_each();
	    return 0;
	}