// 1.cc
// A simple AST, using hierarchy and shared_ptr.

#include <cassert>
#include <iostream>
#include <map>
#include <memory>

#define ECHO(V) std::cerr << #V ": " << (V) << '\n'

struct Exp_impl
{
  virtual std::ostream& print(std::ostream& o) const = 0;
  virtual int eval() const = 0;
};

std::ostream& operator<<(std::ostream& o, const Exp_impl& b)
{
  return b.print(o);
}

using Exp = std::shared_ptr<const Exp_impl>;

/*------.
| Bin.  |
`------*/
struct Bin: Exp_impl
{
  Bin(char o, Exp l, Exp r)
    : op(o)
    , lhs(l)
    , rhs(r)
  {}
  std::ostream& print(std::ostream& o) const
  {
    return o << "(" << *lhs << op << *rhs << ")";
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
  char op;
  Exp lhs, rhs;
};

Exp bin(char op, Exp l, Exp r)
{
  return std::make_shared<const Bin>(op, l, r);
}


/*------.
| Num.  |
`------*/
struct Num: Exp_impl
{
  Num(int v)
    : val(v)
  {}
  std::ostream& print(std::ostream& o) const
  {
    return o << val;
  }
  int eval() const
  {
    return val;
  }
  int val;
};

Exp num(int val)
{
  return std::make_shared<const Num>(val);
}

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
    ECHO(exp->eval());
    assert(exp->eval() == n);
  }
}

