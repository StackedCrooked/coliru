#include <utility>
#include <thread>
#include <iostream>

struct foo{
    void operator()(int i) const {}
};

struct bar{
    bar() { std::cout << "creating " << (void*)this << "\n"; }
    bar(const bar& p) {std::cout<<"copy from " << (void*)&p << " to " << (void*)this << "\n";}
    bar(bar&& p) {std::cout<<"move from " << (void*)&p << " to "<< (void*)this <<"\n";}
    void operator()(const foo& f, int k) const {f(k);}
    ~bar(){std::cout<<"bar::~bar " << (void*)this << "\n";}
};

int main(){
    foo f_1, f_2;
    bar b_1, b_2;
    int i(0), j(0);
    std::cout << "start of loop\n";
    while(i++!=2){
            std::thread t(b_1, std::cref(f_1), i);
            //b_2(f_2, j);
            t.join();
            std::cout << "end of iteration\n";
    }
    std::cout << "end of loop\n";
}