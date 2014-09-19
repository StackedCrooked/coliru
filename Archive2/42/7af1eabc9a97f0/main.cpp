#include <vector>
#include <iostream>
#include <cassert>

static const unsigned VALUE_SIZE_IN_BYTES = 1;
static const unsigned NR_OF_REALLOCATIONS = 20;

using std::cout;
using std::endl;

struct MyType
{
  char someSize[VALUE_SIZE_IN_BYTES];
};

using MyVector = std::vector<MyType>;

int main()
{
  cout.unsetf ( std::ios::floatfield );
  cout.precision(2);

  MyVector vec;
  auto prevCap = vec.capacity();

  for (unsigned cnt = 0; cnt < NR_OF_REALLOCATIONS; ++cnt)
  {
    vec.resize(prevCap);
    assert(vec.capacity() == prevCap);
    vec.push_back(MyType());
    auto cap = vec.capacity();
    assert(vec.capacity() > prevCap);

    if (prevCap)
    {
      auto capBytes = cap * sizeof(MyVector::value_type);
      auto prevCapBytes = prevCap * sizeof(MyVector::value_type);
       cout << "Diff " << capBytes - prevCapBytes
            << " | Ratio " << capBytes << " / " << prevCapBytes
            << " = "<< float(capBytes) / float(prevCapBytes) << endl;
    }

    prevCap = cap;
  }
}
