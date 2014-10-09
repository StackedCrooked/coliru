// 8.2.cc
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

/*------.
| Exp.  |
`------*/

struct Exp_impl;
using Exp = std::shared_ptr<Exp_impl>;

struct Exp_impl
{
  virtual ~Exp_impl() = default;
  virtual std::ostream& print(std::ostream& o) const = 0;
  virtual size_t hash() const = 0;
  virtual bool equals(const Exp_impl& rhs) const = 0;
};

std::ostream& operator<<(std::ostream& o, const Exp_impl& b)
{
  o << "0x" << address(b) << ":";
  return b.print(o);
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
  return b.hash();
}

/*------.
| Bin.  |
`------*/

struct Bin_impl;
using Bin = std::shared_ptr<Bin_impl>;

struct Bin_impl: Exp_impl
{
  // cannot make it private: we need friendship with
  // std::make_shared<Bin_impl>'s internal details, which seems
  // impossible to spell out portably.
  Bin_impl(char o, Exp lhs, Exp rhs)
    : op(o)
    , l(lhs)
    , r(rhs)
  {
    std::cerr << '!' << *this << '\n';
  }

public:
  ~Bin_impl()
  {
    std::cerr << '~' << *this << '\n';
  }

  static Bin make(char o, Exp lhs, Exp rhs)
  {
    static std::map<std::tuple<char, Exp, Exp>, std::weak_ptr<Bin_impl>> map_;
    auto k = std::make_tuple(o, lhs, rhs);
    auto i = map_.find(k);
    if (i == end(map_) || i->second.expired())
      {
        auto res = std::make_shared<Bin_impl>(o, lhs, rhs);
        map_.emplace(k, res);
        return res;
      }
    else
      return Bin(i->second);
  }

  std::ostream& print(std::ostream& o) const
  {
    return o << '(' << l << ' ' << op << ' ' << r << ')';
  }
  size_t hash() const
  {
    size_t res = 0;
    boost::hash_combine(res, boost::hash_value(op));
    boost::hash_combine(res, l);
    boost::hash_combine(res, r);
    return res;
  }
  bool equals(const Exp_impl& rhs_) const
  {
    if (auto rhs = dynamic_cast<const Bin_impl*>(&rhs_))
      return (op == rhs->op
              && l == rhs->l
              && r == rhs->r);
    else
      return false;
  }

  char op;
  Exp l, r;
};

Bin bin(char op, Exp l, Exp r)
{
  return Bin_impl::make(op, l, r);
}



/*------.
| Num.  |
`------*/

struct Num_impl;
using Num = std::shared_ptr<Num_impl>;
struct Num_impl: Exp_impl
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

public:
  static Num make(int v)
  {
    static std::map<int, std::weak_ptr<Num_impl>> map_;
    auto i = map_.find(v);
    if (i == end(map_) || i->second.expired())
      {
        auto res = std::make_shared<Num_impl>(v);
        map_.emplace(v, res);
        return res;
      }
    else
      return Num(i->second);
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
  int val = 0;
};

Num num(int val)
{
  return Num_impl::make(val);
}


/*-------.
| main.  |
`-------*/

int main()
{
  Bin b = bin('+', num(1), num(1));
  ECHO(b);
  Bin e1 = bin('*',
               bin('+', num(1), num(1)),
               bin('+', num(1), num(1)));
  ECHO(b.use_count());
  ECHO(e1.use_count());
  ECHO(e1->l.use_count());
  ECHO(e1);
  ECHO(e1->l);
  Exp e2 = e1;
  ECHO(e1.use_count());
  ECHO(e2);
  Exp e3(e1);
  ECHO(e3);
  ECHO(b.use_count());
}
