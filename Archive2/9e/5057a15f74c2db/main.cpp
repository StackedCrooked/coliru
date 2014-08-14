#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec)
{
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out));
    out << "\n";
    return out;
}

int main (void)
{
    std::vector<int> mas;
    
    int kst = 0;    
    std::cout << "\n\nVvedit` rozmirnist` masyvu: ";
    std::cin >> kst;
    
    int n1 = 0;
    std::cout << "\n\nVvedit` kil`kist` odynyc`: ";
    std::cin >> n1;
    std::cout << "\n";
    assert(n1<=kst);
    
    mas.resize(kst-n1, 0);
    mas.insert(mas.end(), n1, 1);
    
    do {
        std::cout << mas;
    } while(std::next_permutation(mas.begin(), mas.end()));
    
    return 0;
}