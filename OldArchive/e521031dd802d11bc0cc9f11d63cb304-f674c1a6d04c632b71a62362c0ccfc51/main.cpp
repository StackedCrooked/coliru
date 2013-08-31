#include <iostream>
#include <string>
#include <vector>
#include <functional>

struct something
{
      void lel(int i)
      {
            std::cout << "hi!\n" << i << "\n";
      };
};

int main()
{
    something s;
    
    auto f = std::bind(&something::lel, &s, std::placeholders::_1);
    f(42);
}
