#include <algorithm>

// utility for getting an array's size
// usage: array_size(m_vec)
// returns: the number of elements in the array
template<typename T, unsigned long N>
unsigned long array_size(T (&)[N]) { return N; }


struct T {
    double m_vec[3];

    T() {
        std::fill(m_vec, m_vec+array_size(m_vec), 0.0);
    }
};

#include <iterator>
#include <iostream>

int main() {
    T t;
    std::cout << "T: ";
    std::copy(t.m_vec, t.m_vec+3, std::ostream_iterator<int>(std::cout, ", "));
    
}