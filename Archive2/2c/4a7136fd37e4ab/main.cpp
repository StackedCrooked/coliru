#include <iostream>
#include <initializer_list>

struct in_place_t{};

template<typename T>
struct optional
{
    // 1
    template <class... Args>
    constexpr explicit optional(in_place_t, Args&&... args)
    {
        T(std::forward<Args>(args)...);
    }
    
    // 2
    template<class U, class... Args>
    constexpr explicit optional(in_place_t, std::initializer_list<U> il, Args&&... args)
    {
        T(il, std::forward<Args>(args)...);
    }
};

struct foo
{
    foo(std::initializer_list<int>) {}
};

int main()
{
    {
        optional<foo> o(in_place_t{}, {1, 2, 3}); // if you comment 2 out, this will fail
    }
    {
        auto il = {1, 2, 3};
        optional<foo> o(in_place_t{}, il); // this works with or without 2
    }
}
