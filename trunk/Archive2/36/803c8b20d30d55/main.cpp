#include <new>
#include <string>
#include <vector>
#include <iostream>

template<int I> struct tag {};
template<typename First, typename Second>
struct variant {
private:
    static constexpr bool NothrowDestructible =
        std::is_nothrow_destructible<First>()
        && std::is_nothrow_destructible<Second>();

public:
    template<typename... Inits>
    variant(tag<0>, Inits&&... inits)
       : first(std::forward<Inits>(inits)...)
       , active(0)
    {}

    // ditto tag<1> and second

    // move constructor writes itself just as well
    variant(variant const& other)
        : dummy {}
        , active(other.active)
    {
        switch(active) {
        case 0: { ::new (&first) First(other.first); break; }
        case 1: { ::new (&second) Second(other.second); break; }
        }
    }

    // assignment left as an exercise

    ~variant() noexcept(NothrowDestructible)
    {
        switch(active) {
        case 0: { first.~First(); break; }
        case 1: { second.~Second(); break; }
        }
    }
    
    int which() const { return active; }
    
    First& get0() { return first; }

private:
    union {
        // here is why we can't have a variadic pack
        First first;
        Second second;
        unsigned char dummy;
    };
    int active;
};

int main()
{
    variant<std::string, std::vector<int>> v { tag<0> {}, "hello" };
    std::cout << v.which() << '\n';
    std::cout << v.get0() << '\n';
}