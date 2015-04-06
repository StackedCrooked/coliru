#include <iterator>
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>

using Struct_type = int;

template<typename It>
std::vector<Struct_type> boExecute(It Reference_begin, It Reference_end)
{
    std::vector<Struct_type> Out;
    std::copy(Reference_begin, Reference_end, std::back_inserter(Out));
    return Out;
}

int main() {
    std::list<Struct_type> lst {1, 2, 3, 4};
    auto vec = boExecute(begin(lst), end(lst));
    for (auto e : vec) std::cout << e << ' ';
}