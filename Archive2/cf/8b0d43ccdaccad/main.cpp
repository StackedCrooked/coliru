#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

auto List = [](auto ...xs) { 
    return [=](auto access) { return access(xs...); }; 
}; 

auto fmap = [](auto func) {
    return [func] (auto alist) {
        return alist([func](auto... xs) { return List(func(xs)...); });
    };
};

auto concat = [](auto l1, auto l2) {
    auto access1 = [=](auto... p) {
      auto access2 = [=](auto... q) {
        return List(p..., q...);
      };
      return l2(access2);
    };
    return l1(access1);
};

template <class Func>
auto flatten(Func)
{
  return List(); 
}

template <class Func, class A, class... B>
auto flatten(Func f, A a, B... b)
{
  return concat(f(a), flatten(f, b...));
}

auto flatmap = [](auto func) {
    return [func](auto alist) {
        return alist([func](auto... xs) { return flatten(func, xs...);  });
    };
};

auto where_unpleasant = [](auto func) {
  return [=](auto i) { 
      return std::make_pair(func(i), i);
  }; 
};

template <class A, class... B>
struct overload : overload<A>, overload<B...> {
  overload(A a, B... b) 
      : overload<A>(a), overload<B...>(b...) {}  
    using overload<A>::operator ();
    using overload<B...>::operator ();
};
 
template <class A>
struct overload<A> : A{
  overload(A a) 
      : A(a) {} 
  using A::operator();
};

template <class... F>
auto make_overload(F... f) {
  return overload<F...>(f...);   
}

template <class LIST, class Func>
auto operator > (LIST l, Func f)
{
  return fmap(f)(l);   
}

template <class LIST, class Func>
auto operator >= (LIST l, Func f)
{
  return flatmap(f)(l);   
}

template <class M1, class M2>
void assert_equal(M1 m1, M2 m2)
{
  auto to_vector = [](auto... a) { return std::vector<int> { a... }; };
  assert(m1(to_vector) == m2(to_vector));   
}

int main()
{
    auto twice   = [](int i)  { return 2*i; };
    auto print   = [](auto i) { std::cout << i << " "; return i; };
    auto triplet = [](int i)  { return List(-i, 0, i); };
    
    {
      auto l1 = List(1, 2, 3, 4);
      auto l2 = fmap(twice)(l1);
      fmap(print)(l2);
    }
    
    std::cout << "\nMonad-preserving length = ";
    auto pair  = [](auto i) { return List(-i, i); };
    auto count = [](auto... a) { return List(sizeof...(a)); };
    
    {
      auto l1 = List(10, 20, 30);
      auto l2 = flatmap(pair)(l1);
      auto l3 = l2(count);
      fmap(print)(l3);
    }
    
    std::cout << std::endl;
    auto len = [](auto ...z) { return sizeof...(z); }; 
    {
        auto l1 = List(10, 20, 30);
        auto l2 = flatmap(pair)(l1);
        std::cout << "Monad-breaking length = " 
                  << l2(len) 
                  << std::endl;
    }
    
    std::cout << "Overloaded operators\n";
    List(10,20,30) >= pair > print;
    
    std::cout << std::endl;
    auto positive = [](auto i) { return i >= 0; };
    auto pair_print = [](auto pair) { if(pair.first) std::cout << pair.second << " "; return pair.second; };
    List(10, 20) >= pair > where_unpleasant(positive) > pair_print; // prints 10, 20
    
    std::cout << std::endl;
    auto test = 
      make_overload([](int i) { std::cout << "int = " << i << std::endl; },
                    [](double d) { std::cout << "double = " << d << std::endl; });
    test(10); // int 
    test(9.99); // double    

    auto int_or_string = 
        make_overload([](int i) { return 5*i; },
                      [](std::string s) { return s+s; });
    List(10, "ab") > int_or_string  >  print;
        
    std::cout << std::endl;
    
    auto M = List(11);
    std::cout << "Monad law (left identity)\n";
    assert_equal(flatmap(pair)(M), pair(11));
    assert_equal(M >= pair, pair(11));
    
    std::cout << "Monad law (right identity)\n";
    assert_equal(flatmap(List)(M), M);
    assert_equal(M >= List, M);
     
    std::cout << "Monad law (associativity)\n";
    assert_equal(flatmap(triplet)(flatmap(pair)(M)),
                 flatmap([=](auto x) { return flatmap(triplet)(pair(x)); })(M));
    assert_equal(M >= pair >= triplet, 
                 M >= [=](auto x) { return pair(x) >= triplet; });
           
}