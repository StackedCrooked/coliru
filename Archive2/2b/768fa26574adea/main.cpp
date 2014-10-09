// 9.num.cc
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <iostream>
#include <map>

#if 0
# define PING() std::cerr << __PRETTY_FUNCTION__ << '\n'
#else
# define PING()
#endif

#define ECHO(V) std::cerr << #V ": " << (V) << '\n'

/// Name pointers, to make them easier to read.
inline
int address(const void* t)
{
  static std::map<const void*, int> addresses;
  auto p = addresses.emplace(t, 0);
  if (p.second)
    p.first->second = addresses.size();
  return p.first->second;
}

template <typename T>
inline
int address(T* t)
{
  return address((const void*)t);
}

template <typename T>
inline
int address(const T& t)
{
  return address(&t);
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::shared_ptr<T>& b)
{
  if (b)
    o << *b;
  else
    o << "nullptr";
  return o;
}


/*------.
| Num.  |
`------*/

struct Num_impl;
using Num = std::shared_ptr<const Num_impl>;
std::ostream& operator<<(std::ostream& o, const Num_impl& b);

struct Num_impl
{
  //private:
  Num_impl(int v)
    : val(v)
  {
    std::cerr << '!' << *this << '\n';
  }

  ~Num_impl()
  {
    std::cerr << "~" << *this << '\n';
  }

  struct make_num
    : boost::noncopyable
  {
    make_num(int n)
      : res(std::make_shared<Num_impl>(n))
    {}

    Num res;
    operator Num() const { return res; }
  };

public:
  static Num make(int v)
  {
    using flyweight =
      boost::flyweight<boost::flyweights::key_value<int,make_num>>;
    return flyweight(v).get();
  }

  std::ostream& print(std::ostream& o) const
  {
    return o << val;
  }

  int val = 0;
};

std::ostream& operator<<(std::ostream& o, const Num_impl& b)
{
  o << "0x" << address(b) << ":";
  return b.print(o);
}

Num num(int val)
{
  return Num_impl::make(val);
}


/*-------.
| main.  |
`-------*/

int main()
{
  Num n0 = num(42);
  ECHO(n0);
  Num n1 = num(42);
  ECHO(n1);
  Num n2 = n0;
  ECHO(n2);
  Num n3 = num(n0->val + n0->val);
  ECHO(n3);
  Num n4 = num(n3->val);
  ECHO(n4);
}
