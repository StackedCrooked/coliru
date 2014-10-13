// 11.cc
// 
// A version with no inheritance: only variants and flyweight of the
// variant.

#include <boost/variant.hpp>
#include <boost/flyweight.hpp>
#include <iostream>
#include <map>

#if 0
# define PING() std::cerr << __PRETTY_FUNCTION__ << '\n'
#else
# define PING()
#endif

#define ECHO(V) std::cerr << #V ": " << (V) << '\n'

/// Name pointers, to make them easier to read.
struct address
{
  address(const void* t)
  {
    static std::map<const void*, int> addrs;
    auto p = addrs.emplace(t, 0);
    if (p.second)
      p.first->second = addrs.size();
    address_ = p.first->second;
  }

  template <typename T>
  address(T* t)
    : address((const void*)t)
  {}

  template <typename T>
  address(const T& t)
    : address(&t)
  {}

  std::ostream& print(std::ostream& o) const
  {
    return o << "0x" << address_ << ':';
  }

  int address_;
};

std::ostream& operator<<(std::ostream& o, const address& a)
{
  return a.print(o);
}


/*------.
| Exp.  |
`------*/

struct Bin_impl;
struct Num_impl;
using Exp_impl = boost::variant<boost::recursive_wrapper<Bin_impl>, Num_impl>;
using Exp = boost::flyweight<Exp_impl>;

/*------.
| Num.  |
`------*/

struct Num_impl
{
  Num_impl(int v)
    : val(v)
  {}
  int val;
  bool operator==(const Num_impl& that) const
  {
    return val == that.val;
  }
  bool operator!=(const Num_impl& that) const
  {
    return !operator==(that);
  }
};

Exp num(int val)
{
  return Exp(Num_impl(val));
}

/*------.
| Bin.  |
`------*/

struct Bin_impl
{
  Bin_impl(char o, Exp l, Exp r)
    : op(o)
    , lhs(l)
    , rhs(r)
  {}

  char op;
  Exp lhs, rhs;
  bool operator==(const Bin_impl& that) const
  {
    return (op == that.op
            && lhs == that.lhs
            && rhs == that.rhs);
  }
  bool operator!=(const Bin_impl& that) const
  {
    return !operator==(that);
  }
};

Exp bin(char op, Exp l, Exp r)
{
  return Exp(Bin_impl(op, l, r));
}


/*--------.
| print.  |
`--------*/
std::ostream& operator<<(std::ostream& o, const Exp_impl& e);

struct Exp_printer
  : boost::static_visitor<>
{
  Exp_printer(std::ostream& os)
    : o(os)
  {}

  void operator()(const Num_impl& n) const
  {
    o << address(n) << n.val;
  }

  void operator()(const Bin_impl& b) const
  {
    o << address(b) << "(" << b.lhs << b.op << b.rhs << ")";
  }
  std::ostream& o;
};

std::ostream& operator<<(std::ostream& o, const Exp_impl& e)
{
  boost::apply_visitor(Exp_printer(o), e);
  return o;
}

/*-------.
| hash.  |
`-------*/
struct Exp_hasher
  : boost::static_visitor<std::size_t>
{
  std::size_t operator()(const Num_impl& n) const
  {
    return boost::hash_value(n.val);
  }

  std::size_t operator()(const Bin_impl& b) const
  {
    std::size_t res = 0;
    boost::hash_combine(res, boost::hash_value(b.op));
    boost::hash_combine(res, b.lhs);
    boost::hash_combine(res, b.rhs);
    return res;
  }
};

std::size_t hash_value(const Exp_impl& e)
{
  return boost::apply_visitor(Exp_hasher(), e);
}

/*-------.
| eval.  |
`-------*/

class evaluator
  : public boost::static_visitor<int>
{
public:
  int eval(const Exp_impl& e) const
  {
    return boost::apply_visitor(*this, e);  
  }

  int operator()(const Num_impl& n) const
  {
    return n.val;
  }

  int operator()(const Bin_impl& b) const
  {
    switch (b.op)
      {
      case '+': return eval(b.lhs) + eval(b.rhs);
      case '-': return eval(b.lhs) - eval(b.rhs);
      case '*': return eval(b.lhs) * eval(b.rhs);
      case '/': return eval(b.lhs) / eval(b.rhs);
      }
    return 666;
  }
};

int eval(const Exp& e)
{
  return boost::apply_visitor(evaluator(), e.get());  
}


/*-------.
| main.  |
`-------*/

int main()
{
  {
    size_t n = 10 * 1000;
    Exp exp = num(0);
    for (unsigned j = 1; j <= n; ++j)
      {
        Exp e = bin('*',
                    bin('+', num(j), num(j)),
                    bin('+', num(j), num(j)));
        Exp f = bin('/', e, e);
        exp = bin('+', exp, f);
      }
    assert(eval(exp) == n);
  }
}
