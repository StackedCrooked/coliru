#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v {-1, 1, -1, 2, -3, 4, -5, 5, -5};    
    // Gdzie jest 4? Na 5 pozycji.
    std::cerr << std::distance (v.begin (), std::find (v.begin (), v.end (), 4)) << std::endl;

    // Czy w kolekcji występuje liczba 6? NIE!
    std::cerr << (std::find (v.begin (), v.end (), 6) != v.end ()) << std::endl;
    
    // Pierwsza większa od 4 (czyli 5, czyli na pozycji nr. 7).
    std::cerr << std::distance (v.begin (), std::find_if (v.begin (), v.end (), [] (int i) { return i > 4; })) << std::endl;

    // Pierwsza, która NIE jest wieksza od 0 (czyli -1, czyli pozycja nr. 0)
    std::cerr << std::distance (v.begin (), std::find_if_not (v.begin (), v.end (), [] (int i) { return i > 0; })) << std::endl;
}
