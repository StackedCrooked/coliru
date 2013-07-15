#include <initializer_list>
#include <iostream>

struct S {
    S(){ std::cout << "default\n";}
    S(int x){std::cout <<x<<"\n";}
    S(std::initializer_list<int>){std::cout << "foo\n";}
};

int main() {
    S{};
    S{1};
    S{1,2};
    S({5});
    S(42);
}