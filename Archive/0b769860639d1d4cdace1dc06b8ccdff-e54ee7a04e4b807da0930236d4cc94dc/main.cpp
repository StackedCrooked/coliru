#include <iostream>
#include <string>
#include <vector>

using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
    
    int k = 1;
    while (k-->0)
    {
        std::cout << sentence << std::endl;
    }
    
    int iStatus = system( "cd ..; cd ..; cd bin; ls -l; uname;  " );

    if ( !iStatus )
	{
		std::cout << "NOT OK" << std::endl;
	}
	else
	{
		std::cout << "OK" << std::endl;
	}
}
