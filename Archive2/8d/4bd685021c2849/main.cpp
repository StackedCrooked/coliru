#include <algorithm>    // find, remove_if
#include <iostream>
#include <vector>

template<class T>
using M = std::vector<std::vector<T>>; // matrix

template<class T>
std::ostream& operator<<(std::ostream& os, M<T> const& m)
{
    for (auto const& row : m) {
        for (auto const& elem : row)
            os << elem << " ";
        os << "\n";
    }
    return os;
}

template<class T, class IdxIt>
void erase_rows(M<T>& m, IdxIt first, IdxIt last)
{
    m.erase(
        std::remove_if(
            begin(m), end(m), [&](auto& row) {
            auto const row_idx = &row - &m[0];
            return std::find(first, last, row_idx) != last;
        }), 
        end(m)
    );
}

int main()
{
    auto m = M<int> { { 0, 1, 2, 3 }, { 3, 4, 5, 6 }, { 6, 7, 8, 9 }, { 1, 0, 1, 0 } };
    std::cout << m << "\n";
    
    auto drop = { 1, 3 };
    erase_rows(m, begin(drop), end(drop));
    
    std::cout << m << "\n";
}
