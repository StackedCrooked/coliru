#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>


class Class {
public:
  void fun() {
    std::cout << __func__ << std::endl;   
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    std::ostream_iterator<T> out(os, " ");
    std::copy(std::begin(vec), std::end(vec), out);
    
    Class c;
    c.fun();
    
    std::cout << __func__ << std::endl;
    return os;
}


int main() {
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    return 0;
}