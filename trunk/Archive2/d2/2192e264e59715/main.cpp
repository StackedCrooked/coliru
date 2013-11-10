#include <iostream>
#include <sstream>
#include <string>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/assert.hpp>

// D-style input range, consumes input
template<class T>
class DInputRange
{
public:
    explicit DInputRange(std::istream& sin): sin_{sin} 
    { 
        pop_front(); // prime the pump
    }
    
    bool empty() const { return !sin_; }
    void pop_front() { sin_ >> obj_; } // no branching, no nulling out
    T const& front() const { return obj_; }    
private:
    std::istream& sin_;
    T obj_; // no mutable required
};

int main()
{   
    // C-style iteration over an input stream
    std::istringstream sin{"This is his face"};
    std::string s;
    while (sin >> s)
        std::cout << s << " ";
    std::cout << "\n";

    // D-style iteration over an input stream    
    std::istringstream din{"This is his face"};
    for (auto s = DInputRange<std::string>{din}; !s.empty(); s.pop_front())
        std::cout << s.front() << " ";
    std::cout << "\n";
}
