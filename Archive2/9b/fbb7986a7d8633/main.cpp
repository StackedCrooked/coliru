#include <utility>

struct secondchoice {};
struct firstchoice : public secondchoice {};

template <typename T> auto callFunc(T&& t, firstchoice) -> decltype(t.func()) {return t.func();}
template <typename T> void callFunc(T&& t, secondchoice) {}


template <typename T>
void anotherFunc(T&& t) 
{
   callFunc(std::forward<T>(t), firstchoice{});
}


#include <iostream>
struct A
{
   void func() {std::cout << "A";}
};

struct B
{
};


int main() {
    A a;
    anotherFunc(a);
    B b;
    anotherFunc(b);
}