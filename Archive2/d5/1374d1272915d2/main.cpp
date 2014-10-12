// 10.cc
// 
// A version with no inheritance: only variants, no flyweights.

#include <boost/variant.hpp>
#include <iostream>
#include <map>

#if 0
# define PING() std::cerr << __PRETTY_FUNCTION__ << '\n'
#else
# define PING()
#endif

#define ECHO(V) std::cerr << #V ": " << (V) << '\n'

/*------.
| Exp.  |
`------*/

struct Bin_impl;
struct Num_impl;
using Exp = boost::variant<boost::recursive_wrapper<Bin_impl>, Num_impl>;

/*------.
| Num.  |
`------*/

struct Num_impl
{
  Num_impl(int v)
    : val(v)
  {}
  int val;
};

Num_impl num(int val)
{
  return Num_impl(val);
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
};

Bin_impl bin(char op, Exp l, Exp r)
{
  return Bin_impl(op, l, r);
}


/*--------.
| print.  |
`--------*/
std::ostream& operator<<(std::ostream& o, const Exp& e);

struct Exp_printer
  : boost::static_visitor<>
{
  Exp_printer(std::ostream& os)
    : o(os)
  {}

  void operator()(const Num_impl& n) const
  {
    o << n.val;
  }

  void operator()(const Bin_impl& b) const
  {
    o << "(" << b.lhs << b.op << b.rhs << ")";
  }
  std::ostream& o;
};

std::ostream& operator<<(std::ostream& o, const Exp& e)
{
  boost::apply_visitor(Exp_printer(o), e);
  return o;
}


/*-------.
| eval.  |
`-------*/

class evaluator
  : public boost::static_visitor<int>
{
public:
  int eval(const Exp& e) const
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
  return boost::apply_visitor(evaluator(), e);  
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
    ECHO(eval(exp));
    assert(eval(exp) == n);
  }
}
