#include <iostream>
#include <string>
#include <vector>

struct example
{
    enum amount { One,Two,Three };
};

inline example::amount operator|(const example::amount& a, const example::amount& b)
{
  return static_cast<example::amount>(static_cast<int>(a) | static_cast<int>(b));
}

inline example::amount& operator|=(example::amount& a, const example::amount& b)
{
  return a = a | b;
}

int main()
{
    example::amount m(example::One);
    m |= example::Two;
    
    std::cout << "success!";
    return 0;
}
