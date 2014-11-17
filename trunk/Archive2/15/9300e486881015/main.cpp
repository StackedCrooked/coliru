#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v {1, 2, 3, 4, 5, 6, 7, 8, 9};    
    // Gdzie jest 4? Na 3ciej pozycji.
    std::cerr << std::distance (v.begin (), std::search_n (v.begin (), v.end (), 1, 4)) << std::endl;
    // Albo tak:    
    std::cerr << std::distance (v.begin (), std::find (v.begin (), v.end (), 4)) << std::endl;
}
