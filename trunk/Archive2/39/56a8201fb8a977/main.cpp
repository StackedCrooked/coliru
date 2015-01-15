struct S {
    char m_thing[256];
    
    S()
      : m_thing{""} // C++11
    {}
};

#include <algorithm>

struct T {
    char m_thing[256];
    
    // C++03 doesn't include syntax for 'initializing' an array in a constructor
    //   so we just have to assing to it normally
    T() {
        m_thing[0] = '\0';
    }
};

#include <iterator>
#include <iostream>

int main() {
    S s;
    std::cout << "S length: " << std::strlen(s.m_thing) << '\n';


    T t;
    std::cout << "T length: " << std::strlen(t.m_thing) << '\n';

    
}