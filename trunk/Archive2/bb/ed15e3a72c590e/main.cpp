// 7.cc
//
// A Boost.Flyweight-based hash-consing of a simple AST hierarchy.
// There is a single factory for all the types of nodes, stored under
// the base type.
//
// Based on (many) suggestions from Joaquín Mª López Muñoz.

#include <boost/flyweight.hpp>
#include <iostream>
#include <iostream>
#include <map>

#if 0
# define PING() std::cerr << __PRETTY_FUNCTION__ << '\n'
#else
# define PING()
#endif

#define ECHO(V) std::cerr << #V ": " << (V) << '\n'

// A means to name pointers, to be easier to read.
std::map<void*, int> addresses;
template <typename T>
int address(const T& t)
{
  auto p = addresses.emplace((void*)&t, 0);
  if (p.second)
    p.first->second = addresses.size();
  return p.first->second;
}

/*-------------.
| single_ptr.  |
`-------------*/

// Some simple eager smart pointer: when given a value, it steals it,
// and keeps it.  Made to wrap pointers polymorphically in
// Boost.Flyweight.
template <typename Base>
class single_ptr
{
public:
  single_ptr(const Base& x)
    : p(&x)
    , dlt(false)
  {
    PING();
  }
  single_ptr(std::nullptr_t)
    : p(nullptr)
    , dlt(false)
  {
    PING();
  }
  single_ptr(const single_ptr& x)
    : p(x ? x.p->clone() : nullptr)
    , dlt(true)
  {
    PING();
  }
  single_ptr(single_ptr&& x)
    : p(x ? (x.dlt ? x.p : x.p->clone()) : nullptr)
    , dlt(!!x)
  {
    PING();
    if (x)
      x.dlt = false;
  }
  single_ptr& operator=(const single_ptr& x)
  {
    PING();
    Base* q = x ? x.p->clone() : nullptr;
    if (dlt)
      delete p;
    p = q;
    dlt = !!x;
    return *this;
  }
  single_ptr& operator=(single_ptr&& x)
  {
    PING();
    Base* q = x ? x.dlt ? x.p : x.p->clone() : nullptr;
    if (dlt)
      delete p;
    p = q;
    dlt = !!x;
    x.dlt = false;
    return *this;
  }

  ~single_ptr()
  {
    if (dlt)
      delete p;
  }

  operator const Base&() const { return *p; }
  explicit operator bool() const { return p; }

private:
  const Base* p = nullptr;
  bool        dlt;
};

template <typename Base>
std::size_t hash_value(const single_ptr<Base>& x)
{
  return x ? hash_value(static_cast<const Base&>(x)) : 0;
}

template <typename Base>
bool operator==(const single_ptr<Base>& l,
                const single_ptr<Base>& r)
{
  PING();
  if (l)
    return (r
            && static_cast<const Base&>(l)
            ==
            static_cast<const Base&>(r));
  else
    return !r;
}


/*-----------------.
| poly_flyweight.  |
`-----------------*/

template <typename Base>
class poly_flyweight
  : public boost::flyweight<single_ptr<Base>>
{
public:
  using super = boost::flyweight<single_ptr<Base>>;
  using super::super;

  const Base& operator*()  const { return base(); }
  const Base* operator->() const { return &base(); }
  explicit operator bool() const { return static_cast<bool>(this->get()); }

private:
 const Base& base()const { return this->get(); }
};

template <typename Base>
std::size_t hash_value(const poly_flyweight<Base>& x)
{
  return boost::hash<const Base*>()(&*x);
}

template <typename Base>
bool operator==(const poly_flyweight<Base>& l,
                const poly_flyweight<Base>& r)
{
  return (&*l == &*r);
}

template <typename Base>
bool operator!=(const poly_flyweight<Base>& l,
                const poly_flyweight<Base>& r)
{
  return !(l == r);
}

/*-------------------------.
| derived_poly_flyweight.  |
`-------------------------*/

template <typename Derived, typename Base>
class derived_poly_flyweight
  : public poly_flyweight<Base>
{
public:
  using super = poly_flyweight<Base>;
  using super::super;

  //  operator const Derived&()   const { return derived(); }
  const Derived& operator*()  const { return derived(); }
  const Derived* operator->() const { return &derived(); }

private:
  const Derived& derived() const
  {
    return static_cast<const Derived&>(static_cast<const Base&>(this->get()));
  }
};

template <typename Derived, typename Base>
derived_poly_flyweight<Derived, Base>
dynamic_pointer_cast(const poly_flyweight<Base>& b)
{
  using res_t = derived_poly_flyweight<Derived, Base>;
  if (auto res = dynamic_cast<const Derived*>(&*b))
    return res_t(*res);
  else
    return res_t(nullptr);
}


/*------.
| Exp.  |
`------*/

struct Exp_impl
{
  virtual ~Exp_impl() = default;
  virtual Exp_impl* clone() const = 0;
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
  auto res = l.equals(r);
  return res;
}

bool operator!=(const Exp_impl& l, const Exp_impl& r)
{
  return !(l == r);
}

std::size_t hash_value(const Exp_impl& b)
{
  return b.hash();
}

using Exp = poly_flyweight<Exp_impl>;


/*------.
| Bin.  |
`------*/

struct Bin_impl: Exp_impl
{
  Bin_impl(char o, Exp l, Exp r)
    : op(o)
    , lhs(l)
    , rhs(r)
  {}
  Exp_impl* clone() const
  {
    return new Bin_impl(*this);
  }
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
  bool equals(const Exp_impl& x) const
  {
    if (auto that = dynamic_cast<const Bin_impl*>(&x))
      return (op == that->op
              && lhs == that->lhs
              && rhs == that->rhs);
    else
      return false;
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

using Bin = derived_poly_flyweight<Bin_impl, Exp_impl>;
Bin bin(char op, Exp l, Exp r)
{
  return Bin(Bin_impl(op, l, r));
}

/*------.
| Num.  |
`------*/

struct Num_impl: Exp_impl
{
  Num_impl(int v)
    : val(v)
  {}
  Exp_impl* clone() const
  {
    return new Num_impl(*this);
  }
  std::ostream& print(std::ostream& o) const
  {
    return o << val;
  }
  size_t hash() const
  {
    return boost::hash_value(val);
  }
  bool equals(const Exp_impl& rhs) const
  {
    if (auto r = dynamic_cast<const Num_impl*>(&rhs))
      return val == r->val;
    else
      return false;
  }
  int eval() const
  {
    return val;
  }
  int val;
};

using Num = derived_poly_flyweight<Num_impl, Exp_impl>;
Num num(int val)
{
  return Num(Num_impl(val));
}


/*-------.
| main.  |
`-------*/

int main()
{
  if (0)
    {
      Exp zero(nullptr);
      ECHO(static_cast<bool>(zero));

      for (auto i: {1, 2, 3})
        {
          auto a = num(1);
          ECHO(a);
          auto b = num(1);
          ECHO(b);
          auto c = a;
          ECHO(c);
          auto d(a);
          ECHO(d);
        }

      Bin e1 = bin('*',
                   bin('+', num(1), num(1)),
                   bin('+', num(1), num(1)));
      ECHO(e1);
      ECHO(e1->lhs);
      Exp e2 = e1;
      ECHO(e2);
      Exp e3(e1);
      ECHO(e3);
      ECHO(dynamic_pointer_cast<Bin_impl>(e3)->op);
      dynamic_pointer_cast<Num_impl>(e3);
      ECHO(dynamic_pointer_cast<Num_impl>(e3) ? "FAIL" : "pass");
    }

  for (unsigned i = 0; i < 500U * 1000U; ++i)
    {
      Num n = num(1);
      Bin e = bin('*',
                  bin('+', num(1), num(1)),
                  bin('+', num(1), num(1)));
      // Duplicates large parts of e.
      Exp f = bin('/',
                  bin('*',
                      bin('+', num(1), num(1)),
                      bin('+', num(1), num(1))),
                  bin('*',
                      bin('+', num(1), num(1)),
                      bin('+', num(1), num(1))));
      assert(f->eval() == 1);
    }
}
