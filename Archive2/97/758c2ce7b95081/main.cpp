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

template<class... Args>
struct dispatcher{
    std::function<void(Args...)> f;

    void call(){ _call(types<Args...>{}); }
private:
    // take head, produce value from it, pass after other values
    template<class Head, class... Tail, class... Vs>
    void _call(types<Head, Tail...>, Vs&&... vs){
        _call(types<Tail...>{}, std::forward<Vs>(vs)..., get_value<Head>());
    }

    // no more values to produce, forward to callback function
    template<class... Vs>
    void _call(types<>, Vs&&... vs){ f(std::forward<Vs>(vs)...); }
};

void f(int, std::string, int, int){}

int main(){
    dispatcher<int, std::string, int, int> disp{f};
    disp.call();
}