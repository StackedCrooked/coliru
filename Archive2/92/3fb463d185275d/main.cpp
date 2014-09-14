#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>

template<typename T>
void print(T const& x, std::ostream& o)
{
    o << x;
}

template<typename T, typename U>
void print(std::pair<T, U> const& p, std::ostream& o)
{
    o << "(" << p.first << ", " << p.second << ")";
}

template<typename C>
void print_all(C const& c, std::ostream& o)
{
    for (auto x : c) 
    { 
        print(x, o); 
        o << std::endl; 
    }
}

int main()
{    
    std::vector<int> v;
    v.push_back(42);
    v.push_back(1337);
    v.push_back(1729);

    std::map<int, std::string> m;
    m[0] = "Hello";
    m[1] = "World";
    m[2] = "!!";

    print_all(v, std::cout);

    print_all(m, std::cout);
}