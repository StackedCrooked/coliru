#include <functional>
#include <iostream>

template<typename Callable>
void print_target_type(Callable&& thing)
{
    std::cout << "type name: " << std::function<void(int)>(thing).target_type().name() << "\n";
}

struct functor { void operator()(int x) {} };

void free_func(int x) {}

int main() {
    auto lambda = [](int x) { x += 1; };
    print_target_type(lambda);
    std::cout << "target: " << std::function<void(int)>(lambda).target<decltype(lambda)>() << "\n";
    
    print_target_type(functor());
    std::cout << "target: " << std::function<void(int)>(functor()).target<functor>() << "\n";
    
    print_target_type(free_func);
    std::cout << "target: " << std::function<void(int)>(free_func).target<void(*)(int)>() << "\n";
    
    print_target_type(std::bind(free_func, std::placeholders::_1));
    //left as exercise for the reader ;)
}