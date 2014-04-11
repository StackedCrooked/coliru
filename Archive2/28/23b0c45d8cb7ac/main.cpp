#include <iostream>

template <typename X>
struct base
{
private:
    //...

public:
    template <typename I> I next(I i) const { return i(); }
    //...
};

template <typename ZZZ>
struct derived_temp;

struct key { /*...*/ };

using derived = derived_temp <key>;

template <>
struct derived_temp <key> : base <derived>
{
   //...
};

int main() 
{
  std::cout << "Compiled\n";    
}