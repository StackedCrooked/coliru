#include <iostream>
#include <string>
#include <vector>


using Words = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Words & words)
{
    for (const auto & word : words)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Words words = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << words << std::endl;
}

int A, B, C
A = 1
B = 10
C = ""
{
        If A < B;
        {
            C = "a es menor que b";
        }
        Else;
        {
            C = "a no es menor que b";
        }
        End If;
}