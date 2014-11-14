#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v {1, 2, 3, 3, 3, 4};    
    std::cerr << "Ile razy jest 3 : " << std::count (v.begin (), v.end (), 3) << std::endl;
    std::cerr << "Ile jest parzystych : " << std::count_if (v.begin (), v.end (), [] (int i) { return i % 2 == 0; }) << std::endl;
}
