#include <cstdio>
#include <iostream>
#include <utility>

template <typename Result, typename...Args>
struct Wrap {
    template <Result(*callback)(Args...)>
    static Result Func(Args...args) {
        std::cout << "Logging logic goes here...\n";
        return callback(std::forward<Args>(args)...);
    }
};

typedef int (*PrintCallback)(const char *);

int PrintSingle(const char *input)
{
    return std::printf("%s", input);
}

int add(int a, int b){
    std::cout << "adding " << a << " to " << b << '\n';
    return a+b;
};

int main()
{
    PrintCallback pc = Wrap<int, const char*>::Func<PrintSingle>;
    pc("Hello, World!\n");
    
    std::cout << '\n';
    
    auto foo = Wrap<int, int, int>::Func<add>;
    std::cout << foo(2, 3) << '\n';
}