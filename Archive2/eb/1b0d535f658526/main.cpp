struct S {
    double m_vec[3];
    
    S()
      : m_vec{0.0, 0.0, 0.0} // C++11
    {}
};

#include <algorithm>

struct T {
    double m_vec[3];
    
    // C++03 doesn't include syntax for 'initiazling' an array in a constructor
    //   so we just have to assing to it normally
    //   below I use a standard library algorithm instead of using a manual for-loop
    T() {
        std::fill(m_vec, m_vec+3, 0.0);
    }
};

#include <iterator>
#include <iostream>

int main() {
    S s;
    std::cout << "S: ";
    std::copy(s.m_vec, s.m_vec+3, std::ostream_iterator<int>(std::cout, ", "));
    std::cout << '\n';

    T t;
    std::cout << "T: ";
    std::copy(t.m_vec, t.m_vec+3, std::ostream_iterator<int>(std::cout, ", "));
    
}