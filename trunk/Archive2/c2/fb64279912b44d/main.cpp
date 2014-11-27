#include <fstream>
#include <vector>
#include <iostream>

int main()
{
    std::ifstream f("thefile.txt");
    std::vector<int> v;
    for(int n; f >> n; )
        v.push_back(n);
    // done! Print the contents:
    for(int n : v)
        std::cout << n << ' ';
}
