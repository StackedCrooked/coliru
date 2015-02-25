#include <typeinfo>
#include <iostream>
#include <type_traits>

class Item
{
public: 
    template<typename T>
    Item(T&& t)
    {
      std::cout << "!\n";
    }

    
    Item(Item&) = default; // (!)
    
    Item(const Item&) = default;
    Item& operator=(const Item&) = default;
    
    Item(Item&&) noexcept = default;
    Item& operator=(Item&&) noexcept = default;
    
    ~Item() = default;
    
    // ...
};

template<typename T>
void f(T&& o) {
  static_assert(std::is_rvalue_reference<decltype(o)>{}, "");
  Item x{o};
}

template<typename T>
void g(const T& o) {
  f(Item{o});
}

int main() {
  g(4);
}