#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v {1, 1, 1, 2, 3, 4, 5, 5, 5};    
    // Pierwzzy z najmniejszych, czyli pozycja 0.
    std::cerr << "Pozycja najmniejszego : " << std::distance (v.begin (), std::min_element (v.begin (), v.end ())) << std::endl;
    
    // Pierwzy z największych, czyli 6
    std::cerr << "Pozycja największego : " << std::distance (v.begin (), std::max_element (v.begin (), v.end ())) << std::endl;
    
    // Pierwszy z najmniejszych (0) i OSTATNI z największych czyli 8.
    auto p = std::minmax_element (v.begin (), v.end ());
    std::cerr << "Odległość między min i max : " << std::distance (p.first, p.second);
}
