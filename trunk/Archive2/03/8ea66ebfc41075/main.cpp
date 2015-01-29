#include <iostream>
#include <functional>

class LeakedMemory
{
public:
    int v;

	~LeakedMemory()
	{
		std::cout << "Destroyed\n";
	}
};

//void (*lambda)(void) ToLeakOrNotToLeak()
//{
//	LeakedMemory lm{ 5 };
//
//	return []() { std::cout << "Aborto da natureza\n"; };
//}

std::function<void(void)> ToLeakOrNotToLeak()
{
	LeakedMemory lm;

	lm.v = 5;

	return [=]() 
	{ 
		std::cout << "Aborto da natureza\n";
		std::cout << lm.v << std::endl;
		
	};
}

int main(int argc, char* argv [])
{
	auto p = ToLeakOrNotToLeak();

	p();

	return 0;
}