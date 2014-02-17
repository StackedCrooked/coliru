#include <iostream>
#include <utility>
#include <vector>
#include <functional>

template <typename T, template <typename, typename> class C>
struct Bar
{
    using Container = C<T, std::allocator<T>>;
    static Container cont;
    
    #define cmf(name) struct name \
    { \
        template <typename... Args> \
        auto operator()(Args&&... args) -> decltype(cont.name(std::forward<Args>(args)...)) { \
            return cont.name(std::forward<Args>(args)...); \
        } \
    } name;
    
    #define act(name, ...) \
    cmf(name) \
    template <typename... Args> \
    auto act(Args&&... args) -> decltype(name(std::forward<Args>(args)...)) { \
        std::cout << "Debug.\n";
        return name(std::forward<Args>(args)...); \
    } \
    act(__VA_ARGS__)
};

template <typename T, template <typename, typename> class C>
typename Bar<T, C>::Container Bar<T, C>::cont{};

int main() {
    Bar<int, std::vector> bar;
    bar.act(push_back, 42);
    std::cout << bar.cont[0];
    return 0;
}