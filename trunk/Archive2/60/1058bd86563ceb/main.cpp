#include <utility>
#include <iostream>

class CopyableNotMovable
{
public:
  //CopyableNotMovable(CopyableNotMovable &&) =default;
  CopyableNotMovable(const CopyableNotMovable &) {std::cout<<"copy"<<std::endl;}
  CopyableNotMovable()=default;
};

CopyableNotMovable function()
{
  CopyableNotMovable a;
  return std::move(a);
}

int main()
{
  function();
}

