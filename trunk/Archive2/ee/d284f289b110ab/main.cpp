#include <iostream>
#include <map>

#include <boost/range/adaptor/map.hpp>

class A {
  std::map<int,int> my_map = { {0, 1}, {2, 3} };
public:
  decltype(my_map | boost::adaptors::map_values)
  values() { return my_map | boost::adaptors::map_values; }
};

int main() {
    for (const auto& v : A().values())
        std::cout << "v = " << v << std::endl;
    return 0;
}
