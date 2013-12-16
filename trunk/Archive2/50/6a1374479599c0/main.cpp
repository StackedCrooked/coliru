/**
  Distributed under the Boost Software License - Version 1.0
  Author: Sumant Tambe
*/
#include <sys/time.h>
#include <boost/any.hpp>
#include <boost/variant.hpp>
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

  template <class Poly>
  void operator ()(Poly&& p) 
  {
    Lambda::operator()(std::forward<Poly>(p));
  }
};

template <class Lambda>
Otherwise<Lambda> otherwise(Lambda&& l)
{
  return Otherwise<Lambda>(std::forward<Lambda>(l));
}

template <class To, class From>
typename std::enable_if<!is_any<From>::value &&
                        !is_variant<From>::value &&
                        (std::is_class<From>::value ^
                         std::is_class<To>::value), To *>::type 
try_cast(From *) 
{
  return nullptr;
}

template <class To, class From>
typename std::enable_if<!is_any<From>::value &&
                        !is_variant<From>::value &&
                        !std::is_class<From>::value &&
                        !std::is_class<To>::value, To *>::type 
try_cast(From *f) 
{
  if(typeid(From) == typeid(To))
    return (To *) f;
  else
    return nullptr;
}

template <class To, class From>
typename std::enable_if<!is_any<From>::value &&
                        !is_variant<From>::value &&
                         std::is_class<To>::value &&
                         std::is_class<From>::value, To *>::type 
try_cast(From *f) 
{
  return dynamic_cast<To *>(f);
}

template <class To>
To * try_cast(boost::any *a) 
{
  return boost::any_cast<To>(a);
}

template <class To, class... U>
To * try_cast(boost::variant<U...> *v) 
{
  return boost::get<To>(v);
}

template <class To>
const To * try_cast(const boost::any *a) 
{
  return boost::any_cast<To>(a);
}

template <class To, class... U>
const To * try_cast(const boost::variant<U...> *v) 
{
  return boost::get<To>(v);
}

template <class... Fs>
struct type_switch : Fs...
{
  type_switch(Fs... f) 
    : Fs(std::move(f))... 
  {}

  template <class Poly>
  void apply(Poly&& p)  
  {
    bool matched = false;
    bool val[sizeof...(Fs)] = 
      { match_first<Fs>(std::forward<Poly>(p), matched)... };

    (void)val;
  }

private:

  template <class Otherwise, class Poly>
  typename std::enable_if<is_otherwise<Otherwise>::value, bool>::type
  match_first(Poly&& p, bool & matched) 
  {
    if(!matched) {
      (*this)(std::forward<Poly>(p));
      matched = true;
    }
    return true;
  }
 
  template <class Lambda, class Poly>
  typename std::enable_if<!is_otherwise<Lambda>::value, bool>::type
  match_first(Poly&& p, bool & matched) 
  {
    typedef typename function_traits<Lambda>::argument_type arg_type;
    typedef typename std::remove_reference<arg_type>::type noref_type;
    typedef typename add_const_if<std::is_const<Poly>::value, noref_type>::type cast_t;

    if(!matched)
    {
      auto target_ptr = try_cast<cast_t>(&p);
      if(target_ptr) 
      { 
        invoke(target_ptr, typename std::is_reference<Poly>::type());
        matched = true;
      }
    }
    return true;
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
  typedef typename std::remove_const<
    typename std::remove_reference<Variant>::type>::type 
      NoRefVariant;
  std::vector<NoRefVariant> vv;

  vv.push_back(10);
  vv.push_back('Z');
  vv.push_back(std::string("C++ Truths"));
  vv.push_back(10.20);
 
  for(Variant var : vv)
  {
    match(std::move(var))(
      [](int i)                  { std::cout << "int = " << i << "\n"; },
      [](double d)               { std::cout << "double = " << d << "\n"; },
      [](const std::string & s)  { std::cout << "std::string = " << s << "\n"; },
      [](char c)                 { std::cout << "char = " << c << "\n"; },
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
            std::cout << std::boolalpha << boost::any_cast<bool>(a) << "\n";
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

template <class Poly>
void test_poly(Poly& p)
{
  match(p)(
    [](int i)                  { std::cout << "int = "    << i << "\n"; },
    [](double d)               { std::cout << "double = " << d << "\n"; },
    [](const std::string &s)   { std::cout << "string = " << s << "\n"; },
    [](std::ostream &o)        { std::cout << "found ostream"  << "\n"; }
  );  
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
  std::cout << "*********\n";
  test_variant<const Variant>();
  std::cout << "*********\n";
  test_variant<Variant &>();
  std::cout << "*********\n";
  test_variant<const Variant &>();
  std::cout << "*********\n";

  test_switch<boost::any>();
  std::cout << "*********\n";
  test_switch<const boost::any>();
  std::cout << "*********\n";
  test_switch<boost::any &>();
  std::cout << "*********\n";
  test_switch<const boost::any &>();
  std::cout << "*********\n";

  test_rollable();
  std::cout << "*********\n";

  if(argc >= 2)
    test_expr(atoi(argv[1]));

  std::ios_base &stream = std::cout;
  test_poly(stream); 
  boost::any any(std::string("C++ Truths"));
  test_poly(any);
  double d = 9.99;
  test_poly(d);
}