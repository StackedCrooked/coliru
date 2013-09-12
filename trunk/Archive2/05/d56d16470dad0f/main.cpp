#include <string>

auto l = [](std::string){};

template<class T>
auto f(T& v) -> decltype(l(v)){
    return l(v);
}

int main(){
    f("yay for c++11");
}