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

    explicit StrongBitset( string const& str,
      string::size_type pos = 0,
      string::size_type n = string::npos
    )
      : base(str,pos,n)
    {}

    StrongBitset& set() {
      base::set(); return *this;
    }

    StrongBitset& set(size_t pos, bool value = true) {
      base::set(pos, value); return *this;
    }

    StrongBitset& reset() {
      base::reset(); return *this;
    }

    StrongBitset& reset(size_t pos) {
      base::reset(pos); return *this;
    }

    StrongBitset& flip() {
      base::flip(); return *this;
    }

    StrongBitset& flip(size_t pos) {
      base::flip(pos); return *this;
    }

    bitset<Size>& getBase() {
      return *this;
    }

    bitset<Size> const& getBase() const {
      return *this;
    }
  };



template <class Enum, Enum size, bool small = (size<=sizeof(ulong))>
struct compareBitSets;

template <class Enum, Enum size>
struct compareBitSets<Enum, size, false>
{ 
  bool operator()(StrongBitset<Enum, size> const& lhs,  StrongBitset<Enum, size> const& rhs)
  {
    for (unsigned i = 0; i < size; ++i)
    {
      if (lhs[i] != rhs[i]) return rhs[i];
    }
    return false;
  }
};

template <class Enum, Enum size>
struct compareBitSets<Enum, size, true>
{ 
  bool operator()(StrongBitset<Enum, size> const& lhs,  StrongBitset<Enum, size> const& rhs)
  {
    return lhs.to_ulong() < rhs.to_ulong();
  }
};

template <class Enum, Enum size>
bool operator< (StrongBitset<Enum, size> const& lhs,  StrongBitset<Enum, size> const& rhs)
{
  compareBitSets<Enum, size> cmp;   
  return cmp(lhs, rhs);
}


enum E { A, B = 34 };

typedef StrongBitset<E, B> SB;


int main() {
  SB a1;
  SB a2;
  a2.set(1);
  a1.set(0);
  std::cout << (a1 < a2);
}
