#include <iostream>
#include <vector>

namespace lol {

class fuck {
public:
    using iterator = std::vector<int>::iterator;
    fuck() : vec{0, 1, 2, 3, 4, 5} {};
    iterator        legacy_begin()  { return vec.begin(); }
    iterator        legacy_end()    { return vec.end(); }
private:
    std::vector<int> vec;  
};
      
template<class Container> 
auto begin(Container& c) -> decltype(c.legacy_begin()) { return c.legacy_begin(); }

template<class Container> 
auto end(Container& c) -> decltype(c.legacy_end()) { return c.legacy_end(); }

} // namespace lol

int main(int, char*[]) {
    lol::fuck me;
    for (auto& i : me)
        std::cout << i;
    return 0;
}