#include <iostream>
#include <vector>

// global data here

void edge (char from, char to)
{
}

std::vector<char> sort ()
{
    return {};
}

int main()
{
    edge ('F', 'N');
    edge ('H', 'N');
    edge ('N', 'G');
    edge ('G', 'R');
    edge ('F', 'G');
    
    for (auto c : sort ())
    {
        std::cout << c;
    }
    std::cout << '\n';
}
