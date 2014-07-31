#include <iostream>

class Numbers{
public:
  Numbers(){capacity=5; used=0; data = new unsigned long[capacity];}
private:
  unsigned long *data;
  std::size_t used;
  std::size_t capacity;
};

int main()
{
    Numbers n;
    std::cout << "worked!\n";
}