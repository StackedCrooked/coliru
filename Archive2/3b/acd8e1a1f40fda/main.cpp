#include <iostream>
#include <vector>
#include <tuple>

std::vector<std::tuple<int,int,int>> triples = {
  std::make_tuple(1,2,3),
  std::make_tuple(4,5,6),
  std::make_tuple(7,8,9)
};

int main()
{
    int a,b,c;
    for (auto el : triples) {
        std::tie(a,b,c) = el;
    }
    
    std::cout << a << b << c;
}