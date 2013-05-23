#include <iostream>


template<typename T>
void func(T t) { do_func(t); }


int main()
{
    func(1);
}


void do_func(int) { std::cout << "do_func(int)\n"; }
