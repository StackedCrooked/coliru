#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

auto list = [](auto ...xs) { 
    return [=](auto access) { return access(xs...); }; 
};

auto fmap = [](auto func) { 
    return [=](auto ...z) { return list(func(z)...); };
};

auto concat = [](auto l1, auto l2) {
    auto access1 = [=](auto... p) {
      auto access2 = [=](auto... q) {
        return list(p..., q...);
      };
      return l2(access2);
    };
    return l1(access1);
};

template <class Func>
auto flatten(Func)
{
  return list(); 
}

template <class Func, class A>
auto flatten(Func f, A a)
{
  return f(a); 
}

template <class Func, class A, class... B>
auto flatten(Func f, A a, B... b)
{
  return concat(f(a), flatten(f, b...));
}

auto flatmap = [](auto func) {
  return [func](auto... a) { return flatten(func, a...); };
};

auto where_unpleasant = [](auto func) {
  return [=](auto... i) { 
      return list(std::make_pair(func(i), i)...);
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

int main()
{
    auto twice = [](auto i) { return 2*i; };
    auto print = [](auto i) { std::cout << i << " "; return i;};
    list(1, 2, 3, 4)
        (fmap(twice))
        (fmap(print));
    
    std::cout << std::endl;
    auto pair  = [](auto i) { return list(-i, i); };
    auto count = [](auto... a) { return list(sizeof...(a)); };
    list(10, 20, 30)
        (flatmap(pair))
        (count)
        (fmap(print));
    
    std::cout << std::endl;
    auto len = [](auto ...z) { return sizeof...(z); }; 
    std::cout << "Monad-breaking length = " 
              << list(10, 20, 30)
                 (flatmap(pair))
                 (len);
    
    std::cout << std::endl;
    auto positive = [](auto i) { return i >= 0; };
    auto pair_print = [](auto pair) { if(pair.first) std::cout << pair.second << " "; return pair.second; };
    list(10, 20)
        (flatmap(pair))
        (where_unpleasant(positive))
        (fmap(pair_print)); // prints 10, 20
    
    std::cout << std::endl;
    auto test = 
      make_overload([](int i) { std::cout << "int = " << i << std::endl; },
                    [](double d) { std::cout << "double = " << d << std::endl; });
    test(10); // int 
    test(9.99); // double    

    auto int_or_string = 
        make_overload([](int i) { return 5*i; },
                      [](std::string s) { return s+s; });
    list(10, "20")
        (fmap(int_or_string))
        (fmap(print));
        
    auto to_vector = [](auto... a) { return std::vector<int> { a... }; };
    std::cout << std::endl;
    
    auto M = list(11);
    std::cout << "Monad law (left identity)\n";
    assert(M(flatmap(pair))(to_vector) == pair(11)(to_vector));
        
    std::cout << "Monad law (right identity)\n";
    assert(M(flatmap(list))(to_vector) == M(to_vector));
        
    std::cout << "Monad law (associatvity)\n";
    assert(M(flatmap(pair))(flatmap(pair))(to_vector) == 
           M(flatmap([=](auto x) { return pair(x)(flatmap(pair)); }))(to_vector));
           
}