#include <iostream>
#include <string>
#include <functional>

template<class T>
T get_value();

template<>
int get_value(){
    std::cout << "get_value<int>\n";
    return 42;
}

template<>
std::string get_value(){
    std::cout << "get_value<std::string>\n";
    return "hi";
}

template<class...> struct types{};


// no more values to produce, forward to callback function
template<class F, class... Vs>
auto eval_ltr(F f, types<>, Vs&&... vs)
    -> decltype(f(std::forward<Vs>(vs)...))
{ return f(std::forward<Vs>(vs)...); }

// take head, produce value from it, pass after other values
template<class F, class Head, class... Tail, class... Vs>
auto eval_ltr(F f, types<Head, Tail...>, Vs&&... vs)
    -> decltype(eval_ltr(f, types<Tail...>{}, std::forward<Vs>(vs)..., get_value<Head>()))
{
    return eval_ltr(f, types<Tail...>{}, std::forward<Vs>(vs)..., get_value<Head>());
}

void f(int, std::string){}

int main(){
    eval_ltr(f, types<int, std::string>());
}