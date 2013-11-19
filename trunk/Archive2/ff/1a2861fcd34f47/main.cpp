#include <iostream>
#include <type_traits>

template <typename T, bool is_unsigned = std::is_unsigned<T>::type>
class FXP {
     // default implementation here
};
Your next step is to then provide a partial specialization that takes the typename T, but only works for a specific variant of the template parameters (e.g. true or false).

template <typename T>
class FXP<T, false> {
    static const bool arf = false;
};

template <typename T>
class FXP<T, true> {
     static const bool arf = true;
};

int main () {
   
   std::cout << std::boolalpha << FXP<int>::arf;
   std::cout << std::endl;
   std::cout << std::boolalpha << FXP<unsigned int>::arf;
   std::cout << std::endl;
   
}
