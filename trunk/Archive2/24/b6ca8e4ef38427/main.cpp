#include <functional>
#include <iostream>
 
struct foo{ int f(int a) { return a; } };

int fun(int a) { return a; }

int main()
{
    // fn1 and fn2 have the same type, but their targets do not
    foo f;
    std::function<int(int)> fn1(std::bind(&foo::f, &f, std::placeholders::_1));
    std::function<int(int)> fn2(fun);
    std::cout << fn1.target_type().name() << '\n';
    std::cout << fn2.target_type().name() << '\n';
              
    typedef int(*funptr)(int);
    funptr *fptr = fn1.target<funptr>();
    if(!fptr) {
        std::cout << "fn1 nullptr\n";
    }
    
    fptr = fn2.target<funptr>();
    if(!fptr) {
        std::cout << "fn2 nullptr\n";
    }
}
