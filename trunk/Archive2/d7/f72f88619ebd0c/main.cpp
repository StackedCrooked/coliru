#include <iostream>
#include <string>

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
    void (*f)(Args...);
    
    void call(){ _call(types<Args...>{}); }
private:
    template<class Head, class... Tail, class... Collected>
    void _call(types<Head, Tail...>, Collected... c){
        _call<Tail...>(types<Tail...>{}, c..., get_value<Head>());
    }
    
    template<class... Collected>
    void _call(types<>, Collected... c){ f(c...); }
};

void f(int, std::string){}

int main(){
    dispatcher<int, std::string> disp{f};
    disp.call();
}