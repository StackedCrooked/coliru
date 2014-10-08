#include <boost/flyweight.hpp>
#include <iostream>
template<typename Base>
class poly_holder
{
public:
  poly_holder(const Base& x):p(&x),dlt(false){}
  poly_holder(const poly_holder& x):p(x.p->clone()),dlt(true){}
  poly_holder(poly_holder&& x):p(x.dlt?x.p:x.p->clone()),dlt(true){x.dlt=false;}
  poly_holder& operator=(const poly_holder& x)
  {
    Base* q=x.p->clone();
    if(dlt)delete p;
    p=q;
    dlt=true;
    return *this;
  }
  poly_holder& operator=(poly_holder&& x)
  {
    Base* q=x.dlt?x.p:x.p->clone();
    if(dlt)delete p;
    p=q;
    dlt=true;
    x.dlt=false;
    return *this; 
  }
  ~poly_holder(){if(dlt)delete p;}
  
  operator const Base&()const {return *p;}

private:
  const Base* p;
  bool        dlt;
};

template<typename Base>
class poly_flyweight:public boost::flyweight<poly_holder<Base>>
{
public:
  using super=boost::flyweight<poly_holder<Base>>;
  using super::super;
  
  const Base& operator*() const{return base();}
  const Base* operator->()const{return &base();}
  
private:
 const Base& base()const{return this->get();}
};

template<typename Base>
std::size_t hash_value(const poly_flyweight<Base>& x)
{
  return boost::hash<const Base*>()(&*x);
}

template<typename Base>
bool operator==(const poly_flyweight<Base>& l,const poly_flyweight<Base>& r)
{
  return
    static_cast<boost::flyweight<poly_holder<Base>>>(l)==
    static_cast<boost::flyweight<poly_holder<Base>>>(r);
}

template<typename Base>
bool operator!=(const poly_flyweight<Base>& l,const poly_flyweight<Base>& r)
{
  return !(l==r);
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
  virtual ~Base() {}
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

using Exp=poly_flyweight<Base>;

struct Bin: Base
{
  Bin(char o, Exp lhs, Exp rhs)
    : op(o)
    , l(lhs)
    , r(rhs)
  {}
  Base* clone() const
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

Exp bin(char op, Exp l, Exp r)
{
  return Exp(Bin(op, l, r));
}

struct Num: Base
{
  Num(int v)
    : val(v)
  {}
  Base* clone() const
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

Exp num(int val)
{
  return Exp(Num(val));
}

int main()
{
  for (auto i: {1, 2, 3})
  {
    auto a = num(1);
    auto b = num(1);
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';

    std::cout << hash_value(a)
              << ' ' << hash_value(b)
              << ' ' << (a == b) << '\n';
    std::cout << a->hash()
              << ' ' << b->hash()
              << ' ' << (a == b) << '\n';
  }

  Exp e = bin('*',
              bin('+', num(1), num(1)),
              bin('+', num(1), num(1)));
  std::cout << "bin: " << e << '\n';
}