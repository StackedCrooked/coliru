#include <iostream>
#include <string>
#include <vector>
 
template <typename T, typename = decltype(T::Zero)>
auto zero_init_impl(int) -> T { return T::Zero; }
 
template <typename T>
auto zero_init_impl(...) -> T { return T{}; }
 
template <typename T>
auto zero_init() -> T { return zero_init_impl<T>(0); }
 
// Example
struct Special { static Special const Zero; std::string data; };
 
Special const Special::Zero = { "Empty" };
     
int main() {
    std::vector<int> const v{3, zero_init<int>()};
    std::vector<Special> const v2{3, zero_init<Special>()};
     
    std::cout << v[0] << ", " << v[1] << ", " << v[2] << "\n";
    std::cout << v2[0].data << ", " << v2[1].data << ", " << v2[2].data << "\n";
    return 0;
}