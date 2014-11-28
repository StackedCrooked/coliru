#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <cstdlib>

int main()
{
    std::vector <std::string> v1 { "ma", "ala", "ma", "kota" };
    // Uwaga : należy użyć metody std::vector::erase i jako pierwszy argument
    // podać iterator z remove, a drugi to koniec kolekcji. Wtedy te elementy
    // zostaną fizycznie usunięte. 
    v1.erase (std::remove (v1.begin (), v1.end (), "ma"), v1.end ());
    assert ((v1 == std::vector <std::string> { "ala", "kota" }));
}
