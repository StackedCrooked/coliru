#include <iostream>

namespace hi {

  class hello {
 public:
    bool first { true };
  };

}

int main()
{
  hi::hello h ;

  std::cout << "output: " << h.first << std::endl;

  return 0;
}