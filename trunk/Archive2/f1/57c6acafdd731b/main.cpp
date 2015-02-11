#include <iostream>
#include <bitset>
#include <string>
using namespace std;

  template <class Enum, Enum Size>
  struct StrongBitset : public bitset<Size>
  {
    typedef bitset<Size> base;

    StrongBitset() : base() {}
    StrongBitset(unsigned long long val)
      : base(val)
    {}
    //...
  };

#include <climits>


template <class Enum, Enum size, bool small = (size<=CHAR_BIT*sizeof(ulong))>
struct CompareStrongBitsets;

template <class Enum, Enum size>
struct CompareStrongBitsets<Enum, size, false>
{ 
  bool operator()(StrongBitset<Enum, size> const& lhs,  StrongBitset<Enum, size> const& rhs)
  {
    for (unsigned i = 0; i < size; ++i)
    {
      if (lhs[i] != rhs[i]) return lhs[i];
    }
    return false;
  }
};

template <class Enum, Enum size>
struct CompareStrongBitsets<Enum, size, true>
{ 
  bool operator()(StrongBitset<Enum, size> const& lhs,  StrongBitset<Enum, size> const& rhs)
  {
    return lhs.to_ulong() < rhs.to_ulong();
  }
};

template <class Enum, Enum size>
bool operator< (StrongBitset<Enum, size> const& lhs,  StrongBitset<Enum, size> const& rhs)
{
  CompareStrongBitsets<Enum, size> cmp;   
  return cmp(lhs, rhs);
}


enum E { A, B = 3 };

typedef StrongBitset<E, B> SB;


int main() {
  SB a1;
  SB a2;
  a2.set(2);
  a1.set(1);
  std::cout << (a1 < a2);
}
