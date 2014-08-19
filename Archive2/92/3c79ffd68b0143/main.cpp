#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

template<class IteratorIn, class IteratorOut>
void to_string(IteratorIn first, IteratorIn last, IteratorOut out)
{
    std::transform(first, last, out, [](auto d) { return std::to_string(d); } );
}

template<class T>
std::string my_to_string(T v)
{
    std::stringstream ss; 
    ss << v; // Add whatever formatting you want here.
    return ss.str();
}

int main( int argc, char* argv[] )
{
    std::vector<double> v;
    v.push_back(1.0);
    v.push_back(2.1);
    v.push_back(3.2);

    std::vector<std::string> stringVec;
    
    
    // C++03 solution, custom to_string
    std::transform(v.begin(), v.end(), std::back_inserter(stringVec), my_to_string<double> );

    // C++11 solution
    std::transform(v.begin(),
               v.end(), 
               std::back_inserter(stringVec),
               [](double d) { return std::to_string(d); } 
              );
    
    // Same C++11 solution, wrapped in a function template for genericity
    to_string(std::begin(v), std::end(v), std::back_inserter(stringVec));

    for(auto& s : stringVec)
      std::cout << s << '\n';
    
    return 0;
}