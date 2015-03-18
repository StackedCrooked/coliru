// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <unordered_map>
#include <utility>
#include <sstream>
#include <random>

void foo(const std::string& newPosition)
{
    
    std::istringstream convert(newPosition);

	int numberOfConsumers = 0;
	for (unsigned int x = 0; x < 8; ++x)
	{
		for (unsigned int y = 0; y < 8; ++y)
		{
			if (!(convert >> numberOfConsumers))
				numberOfConsumers = 0;
                
                    
            std::cout << numberOfConsumers << std::endl;

			if (numberOfConsumers > 0)
			{
				std::cout << numberOfConsumers << std::endl;
			}
		}
	}
}

std::string bar()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 4);
 
    std::ostringstream tmp;
    
    for (int n=0; n<64; ++n)
        tmp << dis(gen);
        
    return tmp.str();
}

int main ()
{
    std::string pos = bar();
    
                        
    std::cout << pos << std::endl;
    
    foo(pos);

    return 0;
}