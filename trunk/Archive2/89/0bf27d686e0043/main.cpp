#include <type_traits>

int main () {
  struct A { 
    constexpr int operator ()() const {
      return 10; 
    }   
  };  

  static_assert (A {} () == 10, "!!");
}