#include <boost/flyweight.hpp>
#include <iostream>

#if 1
# define PING() std::cerr << __PRETTY_FUNCTION__ << '\n'
#else
# define PING()
#endif

template <typename T>
class poly_flyweight;

template <typename T>
class poly_holder
{
public:
  poly_holder(const T& x)
    : p(&x)
    , dlt(false)
  {
    PING();
  }

  poly_holder(const poly_holder<T>& x)
    : p(x.p->clone())
    , dlt(true)
  {
    PING();
  }

  template <typename U>
  poly_holder(const poly_holder<U>& x)
    : poly_holder(reinterpret_cast<const poly_holder&>(x))
  {
    PING();
  }

  template <typename U>
  poly_holder(const poly_flyweight<U>& x)
    : poly_holder(x.get()) // reinterpret_cast<const poly_flyweight&>(x))
  {
    PING();
  }

  poly_holder(poly_holder&& x)
    : p(x.dlt ? x.p : x.p->clone())
    , dlt(true)
  {
    x.dlt = false;
  }

  poly_holder& operator=(const poly_holder& x)
  {
    PING();
    T* q = x.p->clone();
    if (dlt)
      delete p;
    p = q;
    dlt = true;
    return *this;
  }

  poly_holder& operator=(poly_holder&& x)
  {
    PING();
    T* q = x.dlt ? x.p : x.p->clone();
    if (dlt)
      delete p;
    p = q;
    dlt = true;
    x.dlt = false;
    return *this;
  }

  ~poly_holder()
  {
    if (dlt)
      delete p;
  }

  operator const T&() const { return *p; }

private:
  const T* p;
  bool     dlt;
};

template <typename T>
class poly_flyweight
  : public boost::flyweight<poly_holder<T>>
{
public:
  using super = boost::flyweight<poly_holder<T>>;
  using super::super;

  /// Conversion to superclass.
  template <typename U>
  operator const poly_flyweight<U>&() const
  {
    const void* me = this;
    return *static_cast<const poly_flyweight<U>*>(me);
  }

  template <typename U>
  explicit poly_flyweight(const poly_flyweight<U>& x)
    : poly_flyweight(static_cast<const poly_flyweight&>(x).base())
  {
    PING();
  }

  const T& operator*()  const { return base(); }
  const T* operator->() const { return &base(); }

private:
  const T& base()const { return this->get(); }
};

template <typename T>
std::size_t hash_value(const poly_flyweight<T>& x)
{
  return boost::hash<const T*>()(&*x);
}

template < typename T>
bool operator==(const poly_flyweight<T>& l,
                const poly_flyweight<T>& r)
{
  return (static_cast<boost::flyweight<poly_holder<T>>>(l)
          ==
          static_cast<boost::flyweight<poly_holder<T>>>(r));
}

template <typename T>
bool operator!=(const poly_flyweight<T>& l,
                const poly_flyweight<T>& r)
{
  return !(l == r);
}

#include <iostream>
#include <map>

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

struct Base
{
  virtual ~Base() = default;
  virtual Base* clone() const = 0;
  virtual std::ostream& print(std::ostream& o) const = 0;
  virtual size_t hash() const = 0;
  virtual bool equals(const Base& rhs) const = 0;
};

std::ostream& operator<<(std::ostream& o, const Base& b)
{
  o << "0x" << address(b) << ":";
  return b.print(o);
}

bool operator==(const Base& l, const Base& r)
{
  auto res = l.equals(r);
  return res;
}

bool operator!=(const Base& l, const Base& r)
{
  return !(l == r);
}

std::size_t hash_value(const Base& b)
{
  return b.hash();
}

using Exp = poly_flyweight<Base>;

struct Bin: Base
{
  Bin(char o, Exp lhs, Exp rhs)
    : op(o)
    , l(lhs)
    , r(rhs)
  {}
  virtual Bin* clone() const override
  {
    return new Bin(*this);
  }
  std::ostream& print(std::ostream& o) const
  {
    return o << "(" << l << op << r << ")";
  }
  size_t hash() const
  {
    size_t res = 0;
    boost::hash_combine(res, boost::hash_value(op));
    boost::hash_combine(res, l);
    boost::hash_combine(res, r);
    return res;
  }
  bool equals(const Base& rhs_) const
  {
    if (auto rhs = dynamic_cast<const Bin*>(&rhs_))
      return (op == rhs->op
              && l == rhs->l
              && r == rhs->r);
    else
      return false;
  }

  char op;
  Exp l, r;
};

using BinFW = poly_flyweight<Bin>;

BinFW bin(char op, Exp l, Exp r)
{
  return BinFW(Bin(op, l, r));
}

struct Num: Base
{
  Num(int v)
    : val(v)
  {}
  virtual Num* clone() const override
  {
    return new Num(*this);
  }
  std::ostream& print(std::ostream& o) const
  {
    return o << val;
  }
  size_t hash() const
  {
    return boost::hash_value(val);
  }
  bool equals(const Base& rhs) const
  {
    if (auto r = dynamic_cast<const Num*>(&rhs))
      return val == r->val;
    else
      return false;
  }
  int val;
};

using NumFW = poly_flyweight<Num>;

NumFW num(int val)
{
  return NumFW(Num(val));
}


int main()
{
  NumFW a = num(1);
  std::cout << "num: " << a << '\n';
  Exp b = a;
  std::cout << "exp1: " << b << '\n';
  Exp c(a);
  std::cout << "exp2: " << c << '\n';

  for (auto i: {1, 2, 3})
  {
    auto a = num(1);
    auto b = num(1);
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
  }

  BinFW e1 = bin('*',
                 bin('+', num(1), num(1)),
                 bin('+', num(1), num(1)));
  std::cerr << "Now\n";
  Exp e2 = e1;
  std::cout << "e1: " << e1 << '\n';
  std::cout << "e2: " << e2 << '\n';

  Exp f = bin('/',
              bin('*',
                  bin('+', num(1), num(1)),
                  bin('+', num(1), num(1))),
              num(4));
  std::cout << "f: " << f << '\n';
}
