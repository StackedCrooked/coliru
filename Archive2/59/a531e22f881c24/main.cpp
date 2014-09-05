#include <iostream>
#include <sstream>
#include <stdexcept>

auto list = [](auto ...xs) { 
    return [=](auto access) { return access(xs...); }; 
}; 
    
auto length = [](auto xs) { 
    return xs([](auto ...z) { return sizeof...(z); }); 
}; 

template<class T>
int summand(T t) {
    std::stringstream s;
    s << t << '\n';
    int i;
    s >> i;
    if (s.fail()) {
        throw std::logic_error("Bad arg");
    }
    return i;
}

template<unsigned N, class T0, class... T>
struct Sum {
    static int get(T0 arg, T... args) {
        return summand(arg) + Sum<N - 1, T...>::get(args...);
    }
};

template<class T0>
struct Sum<1, T0> {
    static int get(T0 t) {
        return summand(t);
    }
};

auto sum = [](auto xs) { 
    return xs([](auto ...z) { return Sum<sizeof...(z), decltype(z)...>::get(z...); }); 
};

int main()
{
    std::cout << length(list(1, '2', "3")) << std::endl; // 3
    std::cout << sum(list(1, '2', "3")) << std::endl; // 6
}
