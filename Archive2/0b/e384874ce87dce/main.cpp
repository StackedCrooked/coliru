#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Sometype {};
typedef std::unique_ptr<Sometype> uptr;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


uptr f(){
  uptr p;

  // code setting p = uptr(new sometype(args))

  // return std::move(p); // won't compile without the std::move
  return p; // THIS DOES IN FACT COMPILE
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::cout << "f() does compile" << std::endl;
    uptr x = f();
}
