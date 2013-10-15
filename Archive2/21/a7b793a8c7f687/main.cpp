#include <streambuf>
#include <iterator>

#include <sstream>
#include <iostream>

int main() {
    std::stringstream str("bar");
    
    std::istreambuf_iterator<char> begin(str.rdbuf()), end;
    
    auto begin2(++begin);
    
    std::cout << *begin << *begin2;
}