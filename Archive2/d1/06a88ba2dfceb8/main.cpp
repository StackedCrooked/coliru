#include <utility>
#include <thread>
#include <iostream>

typedef struct foo{
    foo() = default;
    void operator()(int i) const {}
//    ~foo(){std::cout<<"dtor\n";}
} foo;

typedef struct bar{
    bar()           {std::cout<<"bar      " << this << '\n';}
    bar(const bar&) {std::cout<<"bar copy " << this << '\n';}
    bar(bar&&)      {std::cout<<"bar move " << this << '\n';}
    void operator()(const foo& f, int k) const {f(k);}
    ~bar()          {std::cout<<"~bar     " << this << '\n';}
} bar;

int main(){
    foo f_1, f_2;
    bar b_1, b_2;
    int i(0), j(0);
    while(i++!=1){
            std::cout << "---- 1 ----\n";
            std::thread t(std::cref(b_1), std::cref(f_1), i);
            std::cout << "---- 2 ----\n";
            b_2(f_2, j);
            t.join();
            std::cout << "---- 3 ----\n";
    }
}
