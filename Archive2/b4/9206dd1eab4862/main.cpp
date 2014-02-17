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
    
    template <typename Func, typename... Args>
    auto act(Func func, Args&&... args) -> decltype(func(std::forward<Args>(args)...)) {
        return func(std::forward<Args>(args)...);
    }

};

template <typename T, template <typename, typename> class C>
typename Bar<T, C>::Container Bar<T, C>::cont{};

int main() {
    Bar<int, std::vector> bar;


    return 0;
}