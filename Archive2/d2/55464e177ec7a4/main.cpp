#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    {int x = 0;
    int sum = 0;
	
	while (sum>1.7)
	{
        x=x+0.1;
		sum = sum + 1 / x;
        
	}
	
    std::cout << x;
	}
}
