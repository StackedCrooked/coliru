#include <iostream>
#include <string>
#include <vector>
#include <functional>

struct Data
{
  int i;
  Data()                { std::cout << "Data()" << std::endl; }
  Data(const Data& rhs) { std::cout << "Data(const Data&)" << std::endl; i = rhs.i; }
  Data(Data&& rhs)      { std::cout << "Data(Data&&)" << std::endl; i = rhs.i; }
  ~Data()               { std::cout << "~Data()" << std::endl; }
};

Data getDataForceMove()
{
  if (std::rand() == 3)
  {
    Data d;
    d.i = 3;
    return d;
  }
  else
  {
    Data d;
    d.i = 4;
    return d;
  }
}

Data getData()
{
  Data d;
  d.i = 3;
  return d;
}

int main()
{
  const Data& d = getDataForceMove();
  std::cout << d.i << std::endl;
}