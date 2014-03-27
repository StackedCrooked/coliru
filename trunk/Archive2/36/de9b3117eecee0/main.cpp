#include <memory>

class A
{
public:
  std::unique_ptr<int> pint;
};

int main()
{
  A a;
  A b = a;  
}