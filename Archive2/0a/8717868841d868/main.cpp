#include <iostream>                        // cout, endl, << 

//auto apply_list = [](auto cont, auto ...args)
//{
//    return cont(args...);
//}
auto make_list = [](auto ...args)
{ 
    auto applied = [=](auto cont){ 
        return cont(args...);
    };    
    return applied; 
}; 

auto cont_head = [](auto first, auto ...rest)
{ 
    return first; 
};
auto head = [](auto closure_list) 
{ 
    return closure_list(cont_head); 
}; 

auto cont_length = [](auto ...args) 
{ 
    return sizeof...(args); 
};
auto length = [](auto closure_list)
{
    return closure_list(cont_length); 
};

auto fmap = [](auto func) 
{ 
    return [=](auto ...z) { return make_list(func(z)...); };
};
 
 //----------------------------------------------------------
auto cont_tail = [](auto first, auto ...rest)
{ 
        return make_list(rest...); 
}; 
auto tail = [](auto closure_list) 
{ 
    return closure_list(cont_tail); 
}; 
//---------------------------------------------------------- 
auto cont_log = [](auto ...args)
{
        auto comma = "";
        auto print = [&](auto x) { std::cout << comma << x ; comma = ","; return x; };
        std::cout << "[";
        auto result = fmap(print)(args...);        
        std::cout << "]";
        return result;
};
auto log = [](auto closure_list)
{
    return closure_list(cont_log);
};
//----------------------------------------------------------
auto cont_times2 = [](auto ...args)
{
    auto  two = [](auto x) { return 2*x; };
    return fmap(two)(args...);
};    
auto times2 = [](auto closure_list)
{
    return closure_list(cont_times2);
};
//----------------------------------------------------------
int test1()
{
    auto len = length(make_list(1, '2', "3"));    
    std::cout << "len :" << len << std::endl;
    
    auto hd  = head(make_list(1, '2', "3"));    
    std::cout << "head :" << hd << std::endl;
    
    std::cout << "log :"; log(make_list(1, '2', "three")); std::cout << std::endl;
    
    log(               make_list(1,2,3)(cont_times2)(cont_times2) );
    log( times2(times2(make_list(1,2,3)))                         );
    log(        times2(make_list(1,2,3)(cont_times2))            );
    
    std::cout << std::endl;
    
    log(times2(make_list(1,2,3)(cont_log))(cont_tail));
   
    return 0;
}


auto concat = [](auto l1, auto l2) {
    auto access1 = [=](auto... p) {
      auto access2 = [=](auto... q) {
        return make_list(p..., q...);
      };
      return l2(access2);
    };
    return l1(access1);
};
 
template <class Func>
auto flatten(Func)
{
  return make_list(); 
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

void test2()
{
    auto pair  = [](auto i)     { return make_list(-i, i); };
    auto count = [](auto... a)  { return make_list(sizeof...(a)); };
    make_list(10, 20, 30)
    (flatmap(pair))
    (count)
    (cont_log); // prints 6.
}

int main()
{
    test2();
    //test1();
}


