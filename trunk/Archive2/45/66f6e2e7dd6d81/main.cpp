// 9.cc
//
// Use a factory per concrete AST type.
//
// /Exp_impl/ is the AST base class.
//
// Bin_impl and Num_impl derive from it, but we don't build these
// value directly: rather we use a per-type Flyweight that returns a
// specific type: Num = flyweight_ptr<Num_impl> and Bin =
// flyweight_ptr<Bin_impl>.
//
// We are left with the problem of storing polymorphically Num and Bin
// (contrary to shared_ptr, hierarchies do not "traverse"
// flyweight_ptr).
//
// The class Exp does that: it stores different flyweight_ptr types.

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <iostream>
#include <map>

#define CERR_(V) std::cerr << V << '\n'

#if 0
# define CERR(V) CERR_(V)
#else
# define CERR(V)
#endif

#define PING() CERR(__PRETTY_FUNCTION__)
#define ECHO(V) CERR_(#V ": " << (V))

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

template <typename T>
struct flyweight_ptr
  : boost::flyweight<T>
{
public:
  using super = boost::flyweight<T>;
  using super::super;

  const T& operator*()  const { return base(); }
  const T* operator->() const { return &base(); }

private:
 const T& base()const { return this->get(); }
};


/*-----------.
| Exp_impl.  |
`-----------*/

struct Exp_impl
{
  virtual ~Exp_impl() = default;
  virtual std::ostream& print(std::ostream& o) const = 0;
  virtual size_t hash() const = 0;
  virtual bool equals(const Exp_impl& rhs) const = 0;
  virtual int eval() const = 0;
};

std::ostream& operator<<(std::ostream& o, const Exp_impl& b)
{
  o << "0x" << address(b) << ":";
  return b.print(o);
}

bool operator==(const Exp_impl& l, const Exp_impl& r)
{
  return l.equals(r);
}

bool operator!=(const Exp_impl& l, const Exp_impl& r)
{
  return !(l == r);
}

std::size_t hash_value(const Exp_impl& b)
{
  PING();
  auto res = b.hash();
  CERR("hash(" << b << ") = " << res);
  return res;
}

/*------.
| Exp.  |
`------*/

/// A structure that stores flyweights of different types that all
/// contain classes derived from Exp_impl.
struct Exp
{
  struct Holder
  {
    virtual ~Holder() = default;
    virtual const Exp_impl& get() const = 0;
  };

  template <typename T>
  struct Holder_impl: Holder
  {
    Holder_impl(T v)
      : value(v)
    {}

    const Exp_impl& get() const
    {
      PING();
      return *value;
    }

    T as() const
    {
      return value;
    }

    T value;
  };

  template <typename T>
  Exp(T v)
    : value(std::make_shared<Holder_impl<T>>(v))
  {}

  template <typename T>
  T as() const
  {
    auto h = std::dynamic_pointer_cast<Holder_impl<T>>(value);
    assert(h);
    return h->as();
  }

  const Exp_impl& operator*() const { return value->get(); }
  const Exp_impl* operator->()const { return &value->get(); }

  bool operator==(const Exp& that) const
  {
    return operator*() == *that;
  }

private:
  std::shared_ptr<Holder> value;
};

std::ostream& operator<<(std::ostream& o, const Exp& b)
{
  return b->print(o);
}

size_t hash_value(const Exp& that)
{
  PING();
  return hash_value(*that);
}



/*------.
| Bin.  |
`------*/

struct Bin_impl;

std::ostream& operator<<(std::ostream& o, const Bin_impl& b);

struct Bin_impl: Exp_impl
{
  //private:
  Bin_impl(char o, Exp l, Exp r)
    : op(o)
    , lhs(l)
    , rhs(r)
  {
    CERR('!' << *this);
  }

  ~Bin_impl()
  {
    CERR('~' << *this);
  }

public:
  std::ostream& print(std::ostream& o) const
  {
    return o << "(" << lhs << op << rhs << ")";
  }
  size_t hash() const
  {
    size_t res = 0;
    boost::hash_combine(res, boost::hash_value(op));
    boost::hash_combine(res, lhs);
    boost::hash_combine(res, rhs);
    return res;
  }
  int eval() const
  {
    switch (op)
      {
      case '+': return lhs->eval() + rhs->eval();
      case '-': return lhs->eval() - rhs->eval();
      case '*': return lhs->eval() * rhs->eval();
      case '/': return lhs->eval() / rhs->eval();
      }
    return 666;
  }
  bool equals(const Exp_impl& x) const
  {
    if (auto that = dynamic_cast<const Bin_impl*>(&x))
      return (op == that->op
              && lhs == that->lhs
              && rhs == that->rhs);
    else
      return false;
  }

  char op;
  Exp lhs, rhs;
};

using Bin = flyweight_ptr<Bin_impl>;



/*------.
| Num.  |
`------*/

struct Num_impl;

std::ostream& operator<<(std::ostream& o, const Num_impl& b);

struct Num_impl: Exp_impl
{
  //private:
  Num_impl(int v)
    : val(v)
  {
    CERR('!' << *this);
  }

  Num_impl(const Num_impl& x)
    : val(x.val)
  {
    CERR('#' << *this);
  }

  Num_impl(Num_impl&& x)
    : val(std::move(x.val))
  {
    CERR('<' << *this);
  }

  ~Num_impl()
  {
    CERR('~' << *this);
  }

public:
  std::ostream& print(std::ostream& o) const
  {
    return o << val;
  }

  size_t hash() const
  {
    PING();
    return boost::hash_value(val);
  }
  bool equals(const Exp_impl& rhs) const
  {
    PING();
    if (auto r = dynamic_cast<const Num_impl*>(&rhs))
      return val == r->val;
    else
      return false;
  }
  int eval() const
  {
    return val;
  }

  int val = 0;
};

using Num = flyweight_ptr<Num_impl>;


/*-------.
| main.  |
`-------*/

int main()
{
if (0)
  for (int i = 0; i < 2; ++i)
    {
      Num n(42);
      ECHO(n);
      Num a(51);
      ECHO(a);
      Num b(42);
      ECHO(b);

      Num n2(n);
      ECHO(n2);
      Num n3 = n2;
      ECHO(n3->val);
      Exp e = n;
      ECHO(e.as<Num>());
      Bin b1('+', n, e);
      ECHO(b1);
      ECHO(b1->lhs);
      ECHO(b1->lhs.as<Num>());
    }

  for (unsigned i = 0; i < 500 * 1000; ++i)
    {
      Num n = Num(1);
      Bin e = Bin('*',
                  Bin('+', Num(1), Num(1)),
                  Bin('+', Num(1), Num(1)));
      // Duplicates large parts of e.
      Exp f = Bin('/',
                  Bin('*',
                      Bin('+', Num(1), Num(1)),
                      Bin('+', Num(1), Num(1))),
                  Bin('*',
                      Bin('+', Num(1), Num(1)),
                      Bin('+', Num(1), Num(1))));
      assert(f->eval() == 1);
    }
}
