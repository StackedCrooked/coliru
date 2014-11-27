#include <fstream>
#include <vector>
#include <iostream>

int main()
{
    std::ifstream f("thefile.txt");
    std::vector<int> v{ std::istream_iterator<int>(f),
                        std::istream_iterator<int>() };
    // done! Print the contents:
    for(int n : v)
        std::cout << n << ' ';
}
