#include <iostream>
#include <type_traits>

template <typename T, bool is_unsigned = std::is_unsigned<T>::value>
class FXP {
public:
     static const bool arf = false;
};

template <typename T>
class FXP<T, true> {
public:
    static const bool arf = true;
};

int main () {
   std::cout << std::boolalpha;
   
   std::cout << FXP<int>::arf << std::endl;;
   std::cout << FXP<unsigned int>::arf << std::endl;;
   
}
