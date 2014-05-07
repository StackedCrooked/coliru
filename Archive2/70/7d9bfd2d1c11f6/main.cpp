/**
  Distributed under the Boost Software License - Version 1.0
  Author: Sumant Tambe
*/
#include <sys/time.h>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <type_traits>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

template <typename T>
struct function_traits
{
  typedef typename function_traits<decltype(&T::operator())>::return_type return_type;
  typedef typename function_traits<decltype(&T::operator())>::argument_type argument_type;
};

template <typename R, typename C, typename A>
struct function_traits<R (C::*)(A)> 
{
  typedef R return_type;
  typedef A argument_type;
};

template <typename R, typename C, typename A>
struct function_traits<R (C::*)(A) const> 
{
  typedef R return_type;
  typedef A argument_type;
};

template <typename R, typename A>
struct function_traits<R (*)(A)>
{
  typedef R return_type;
  typedef A argument_type;
};

template <bool Val, class T = void>
using disable_if = std::enable_if<!Val, T>;

template <class T>
using no_ref = typename std::remove_reference<T>::type;

template <class Lambda>
struct Otherwise;

template <class T>
struct is_otherwise : std::false_type {};

template <class T>
struct is_otherwise<Otherwise<T>> : std::true_type {};

template <class T>
struct is_otherwise<const Otherwise<T>> : std::true_type {};

template <class T>
struct is_any : std::false_type {};

template <>
struct is_any<boost::any> : std::true_type {};

template <>
struct is_any<const boost::any> : std::true_type {};

template <class T>
struct is_variant : std::false_type {};

template <class... U>
struct is_variant<boost::variant<U...>> : std::true_type {};

template <class... U>
struct is_variant<const boost::variant<U...>> : std::true_type {};

template <bool, class Op>
struct add_const_if {
  typedef Op type;
};

template <class Op>
struct add_const_if<true, Op> {
  typedef const Op type;
};

template <class Lambda>
struct Otherwise : Lambda
{
  Otherwise(Lambda l) : Lambda(std::move(l)) {}
  using Lambda::operator();
};

template <class Lambda>
Otherwise<Lambda> otherwise(Lambda&& l)
{
  return Otherwise<Lambda>(std::forward<Lambda>(l));
}

template <class To, class From>
typename std::enable_if<!is_any<From>::value &&
                         std::is_polymorphic<From>::value &&
                        !std::is_polymorphic<To>::value, To *>::type 
try_cast(From *) 
{
  return nullptr;
}

template <class To, class From>
typename std::enable_if<!is_any<From>::value &&
                         std::is_polymorphic<From>::value &&
                         std::is_polymorphic<To>::value, To *>::type 
try_cast(From *f) 
{
  return dynamic_cast<To *>(f);
}

template <class To>
To * try_cast(boost::any *a) 
{
  return boost::any_cast<To>(a);
}

template <class To>
const To * try_cast(const boost::any *a) 
{
  return boost::any_cast<To>(a);
}

template <class... Fs>
struct type_switch : Fs..., boost::static_visitor<void>
{
private:
  template <class Head, class... Tail>
  struct ChainOfResponsibility
  {
    template <class TypeSwitch, class Poly>
    static void call(TypeSwitch& ts, Poly&& p, bool & matched) 
    {
      if(!matched)
      {
        ts.template match<Head>(std::forward<Poly>(p), matched);
        if(!matched)
          ChainOfResponsibility<Tail...>::call(ts, std::forward<Poly>(p), matched);
      }
    }
  };

  template <class LastFunctor>
  struct ChainOfResponsibility<LastFunctor>
  {
    template <class TypeSwitch, class Poly>
    static void call(TypeSwitch& ts, Poly&& p, bool & matched) 
    {
      if(!matched) 
        ts.template match<LastFunctor>(std::forward<Poly>(p), matched);
    }
  };
  
  template <class Lambda, class... Functor>
  struct ChainOfResponsibility<Otherwise<Lambda>, Functor...>
  {
    template <class TypeSwitch, class Poly>
    static void call(TypeSwitch& ts, Poly&& p, bool & matched) 
    {
      if(!matched) 
      {
        ChainOfResponsibility<Functor...>::call(ts, std::forward<Poly>(p), matched);
        ChainOfResponsibility<Otherwise<Lambda>>::call(ts, std::forward<Poly>(p), matched);
      }
    }
  };
  
  template <class Lambda>
  struct ChainOfResponsibility<Otherwise<Lambda>>
  {
    template <class TypeSwitch, class Poly>
    static void call(TypeSwitch& ts, Poly&& p, bool & matched) 
    {
      if(!matched) 
        ts.Otherwise<Lambda>::operator()(std::forward<Poly>(p));
    }
  };
  
public:
  type_switch(Fs... f) 
    : Fs(std::move(f))... 
  {}

  template <class Poly>
  typename std::enable_if<is_variant<no_ref<Poly>>::value>::type
  apply(Poly&& p)  
  {
    boost::apply_visitor(*this, std::forward<Poly>(p));
  }

  template <class Poly>
  typename std::enable_if<!is_variant<no_ref<Poly>>::value&&
                          (is_any<no_ref<Poly>>::value ||
                           std::is_polymorphic<no_ref<Poly>>::value)>::type
  apply(Poly&& p)  
  {
    bool matched = false;
    ChainOfResponsibility<Fs...>::call(*this, std::forward<Poly>(p), matched);
  }

  template <class Poly>
  typename std::enable_if<!is_variant<no_ref<Poly>>::value &&
                          !is_any<no_ref<Poly>>::value &&
                          !std::is_polymorphic<no_ref<Poly>>::value>::type
  apply(Poly&& p)  
  {
    (*this)(std::forward<Poly>(p));
  }

private:
 
  template <class Lambda, class Poly>
  void match(Poly&& p, bool & matched) 
  {
    typedef typename function_traits<Lambda>::argument_type arg_type;
    typedef typename add_const_if<std::is_const<Poly>::value, 
                                  no_ref<arg_type>>::type cast_t;

    auto target_ptr = try_cast<cast_t>(&p);
    if(target_ptr) 
    { 
      invoke(target_ptr, typename std::is_reference<Poly>::type());
      matched = true;
    }
  }

  template <class U>
  void invoke(U *target_ptr, std::true_type /* is_reference */) 
  {
    (*this)(*target_ptr);
  }

  template <class U>
  void invoke(U *target_ptr, std::false_type /* is_reference */) 
  {
    (*this)(std::move(*target_ptr));
  }
};

template <class T>
class Matcher
{
  typedef typename std::add_rvalue_reference<T>::type TRef;
  TRef t_;
public:  
  Matcher(TRef t) : t_(std::forward<T>(t)) {}

  template <class... Fs>
  void operator()(Fs&&... f)  
  {
    type_switch<Fs...>(std::forward<Fs>(f)...).apply(std::forward<T>(t_));
  }
};

template <class T>
Matcher<T> match(T&& t)
{
  return Matcher<T>(std::forward<T>(t));
}

template <class... Fs>
struct TypeSwitchApplicator
{
  type_switch<Fs...> ts_;

  TypeSwitchApplicator(type_switch<Fs...> ts)
    : ts_(std::move(ts))
  {}

  template <class Arg>
  void operator ()(Arg&& arg) 
  {
    ts_.apply(std::forward<Arg>(arg));
  }
};

template <class... Fs>
TypeSwitchApplicator<Fs...> typeswitch(Fs&&... f)
{
  return type_switch<Fs...>(std::forward<Fs>(f)...);
}

template <class T>
void test_any(void)
{
  std::vector<boost::any> va;
  va.push_back(10);
  va.push_back('Z');
  va.push_back(std::string("C++ Truths"));
  va.push_back(10.20);
  va.push_back(true);
 
  for(T any : va)
  {
    match(std::move(any))(
      [](int i) mutable          { std::cout << "int = " << i << "\n"; },
      [](double d)               { std::cout << "double = " << d << "\n"; },
      [](std::string & s)        { std::cout << "lvalue std::string = " << s << "\n"; },
      [](std::string && s)       { std::cout << "rvalue std::string = " << s << "\n"; },
      [](const std::string & s)  { std::cout << "const lvalue std::string = " << s << "\n"; },
      [](const std::string && s) { std::cout << "const rvalue std::string = " << s << "\n"; },
      [](char c)                 { std::cout << "char = " << c << "\n"; },
      otherwise([](boost::any a) { 
        std::cout << "Otherwise: pass-by-value any: "; 
        if(typeid(bool) == a.type())
          std::cout << std::boolalpha << boost::any_cast<bool>(a) << "\n";
      }) 
    );
  }
}

template <class Variant>
void test_variant()
{
  typedef typename 
    std::remove_const<no_ref<Variant>>::type NoRefVariant;
  std::vector<NoRefVariant> vv;

  vv.push_back(10);
  vv.push_back('Z');
  vv.push_back(std::string("C++ Truths"));
  vv.push_back(10.20);
 
  for(Variant var : vv)
  {
    match(var)(
      [](int &i)                  { std::cout << "int = " << i << "\n"; },
      [](double &d)               { std::cout << "double = " << d << "\n"; },
      [](std::string & s)         { std::cout << "string = " << s << "\n"; },
      [](char &c)                 { std::cout << "char = " << c << "\n"; },
      [](const int &i)            { std::cout << "const int = " << i << "\n"; },
      [](const double &d)         { std::cout << "const double = " << d << "\n"; },
      [](const std::string & s)   { std::cout << "const string = " << s << "\n"; },
      [](const char &c)           { std::cout << "const char = " << c << "\n"; },
      otherwise([](NoRefVariant var) {
        std::cout << "Otherwise: pass-by-value variant: no match found\n"; 
        }) 
    );
  }
}

template <class T>
void test_switch()
{
  std::vector<boost::any> va;
  va.push_back(10);
  va.push_back('Z');
  va.push_back(std::string("C++ Truths"));
  va.push_back(10.20);
  va.push_back(true);
  
  std::function<void(T)> ts = 
    typeswitch(
        [](int i)                  { std::cout << "int = " << i << "\n"; },
        [](double d)               { std::cout << "double = " << d << "\n"; },
        [](std::string & s)        { std::cout << "lvalue std::string = " << s << "\n"; },
        [](std::string && s)       { std::cout << "rvalue std::string = " << s << "\n"; },
        [](const std::string & s)  { std::cout << "const lvalue std::string = " << s << "\n"; },
        [](const std::string && s) { std::cout << "const rvalue std::string = " << s << "\n"; },
        [](char c)                 { std::cout << "char = " << c << "\n"; },
        otherwise([](boost::any a) { 
          std::cout << "otherwise: pass-by-value any: "; 
          if(typeid(bool) == a.type())
            std::cout << std::boolalpha << boost::any_cast<bool>(a);
          std::cout << "\n";
        }));

  for(T any : va)
  {
    ts(any);
  }
}

struct Expr { 
  virtual ~Expr() {}
  virtual int exec() const = 0;
};

struct Value : Expr {
  Value(int v) : value(v) {}
  int exec() const override { return value; }
  int value;
};

struct Plus : Expr {
  Plus(const Expr& e1, const Expr& e2) 
    : e1(e1), e2(e2) 
  {}
  int exec() const override {
    return e1.exec() + e2.exec();
  }
  const Expr& e1;
  const Expr& e2;
};

struct Minus : Expr {
  Minus(const Expr& e1, const Expr& e2) : e1(e1), e2(e2) {}
  int exec() const override {
    return e1.exec() - e2.exec();
  }
  const Expr& e1;
  const Expr& e2;
};

struct Times : Expr {
  Times(const Expr& e1, const Expr& e2) : e1(e1), e2(e2) {}
  int exec() const override {
    return e1.exec() * e2.exec();
  }
  const Expr& e1;
  const Expr& e2;
};

struct Divide : Expr {
  Divide(const Expr& e1, const Expr& e2) : e1(e1), e2(e2) {}
  int exec() const override {
    return e1.exec() / e2.exec();
  }
  const Expr& e1;
  const Expr& e2;
};

int eval(const Expr& expr)
{
  int val = 0;
  match(expr)(
    [&](const Value&  x) { val = x.value; },
    [&](const Plus&   x) { val = eval(x.e1) + eval(x.e2); },
    [&](const Minus&  x) { val = eval(x.e1) - eval(x.e2); },
    [&](const Times&  x) { val = eval(x.e1) * eval(x.e2); },
    [&](const Divide& x) { val = eval(x.e1) / eval(x.e2); }
  );
  return val;
}

int operator - (const timeval & end, const timeval & start)
{
  return (end.tv_sec*1000+end.tv_usec/1000)-(start.tv_sec*1000+start.tv_usec/1000);
}

void test_expr(int iter)
{
  timeval start, stop;
  gettimeofday(&start, nullptr);
  for(int i=0;i < iter;++i)
  {
    eval(Times(Plus(Value(10), Value(20)), Plus(Value(5), Value(10))));
    //std::cout << "eval = " 
    //        << eval(Times(Plus(Value(10), Value(20)), Plus(Value(5), Value(10))))
    //        << std::endl;
  }
  gettimeofday(&stop, nullptr);
  std::cout << "Diff = " << stop - start << std::endl;
  
  gettimeofday(&start, nullptr);
  for(int i=0;i < iter;++i)
  {
    Times(Plus(Value(10), Value(20)), Plus(Value(5), Value(10))).exec();
    //std::cout << "eval = " 
    //        << eval(Times(Plus(Value(10), Value(20)), Plus(Value(5), Value(10))))
    //        << std::endl;
  }
  gettimeofday(&stop, nullptr);
  std::cout << "Diff = " << stop - start << std::endl;
}

struct Shape
{
  virtual ~Shape() {}
};

struct Rollable 
{
  virtual ~Rollable() {}
};

struct Circle : Shape, Rollable {};
struct Triangle : Shape {};
struct Square : Shape {};

void test_rollable()
{
  Square s1, s2;
  Circle c1, c2;
  Triangle t1;
  std::vector<Shape *> vs;

  vs.push_back(&s1);
  vs.push_back(&s2);
  vs.push_back(&c1);
  vs.push_back(&c2);
  vs.push_back(&t1);

  for(Shape *s : vs)
  {
    match(*s)(
      [](Square &s)    { std::cout << "square\n"; },
      [](Rollable &r)  { std::cout << "rollable\n"; },
      otherwise([](Shape &s) {
          std::cout << "generic shape\n";
      })
    );
  }
}

struct generic_lambda
{
  template <class T>
  void operator ()(T &) { std::cout << "don't know\n"; }
};

class Base {};
class Derived1 : public Base {};
class Derived2 : public Derived1 {};

template <class Poly>
void test_poly(Poly& p)
{
  match(p)(
    otherwise(generic_lambda()),
    [](int i)                         { std::cout << "int = "    << i << "\n"; },
    [](double d)                      { std::cout << "double = " << d << "\n"; },
    [](const std::string &s)          { std::cout << "const string = " << s << "\n"; },
    [](std::string &s)                { std::cout << "string = " << s << "\n"; },
    [](const std::ostream &o)         { std::cout << "found ostream\n";        },
    [](const std::basic_ios<char> &)  { std::cout << "found basic_ios\n";      },
    [](const Base &)                  { std::cout << "found Base\n";           },
    [](Derived2 &)                    { std::cout << "found Derived2\n";       }
  );  
}

void test_mixed()
{
  std::ios_base &stream = std::cout;
  boost::any any(std::string("C++ Truths"));
  double d = 9.99;
  char c = 'Z';
  boost::variant<int, std::string> var("boost");
  enum Color { Red=1, Green=2, Blue=3 };
  Color color = Red;
  Derived2 d2;
  
  test_poly(stream); 
  test_poly(any);
  test_poly(d);
  test_poly(var);
  test_poly(c);
  test_poly(color);
  test_poly(d2);
}

int main(int argc, char *argv[])
{
  test_any<boost::any>();
  std::cout << "*********\n";
  test_any<const boost::any>();
  std::cout << "*********\n";
  test_any<boost::any &>();
  std::cout << "*********\n";
  test_any<const boost::any &>();
  std::cout << "*********\n";

  typedef boost::variant<int, char, std::string, double> Variant;
  test_variant<Variant>();
  std::cout << "#########\n";
  test_variant<const Variant>();
  std::cout << "#########\n";
  test_variant<Variant &>();
  std::cout << "#########\n";
  test_variant<const Variant &>();
  std::cout << "#########\n";

  test_switch<boost::any>();
  std::cout << "@@@@@@@@@\n";
  test_switch<const boost::any>();
  std::cout << "@@@@@@@@@\n";
  test_switch<boost::any &>();
  std::cout << "@@@@@@@@@\n";
  test_switch<const boost::any &>();
  std::cout << "@@@@@@@@@\n";

  test_rollable();
  std::cout << "*********\n";

  if(argc >= 2)
    test_expr(atoi(argv[1]));

  test_mixed();
}