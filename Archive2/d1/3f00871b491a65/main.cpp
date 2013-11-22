#include <type_traits>

struct Nontemplate {
    auto f() -> decltype(this)
    {
        static_assert(std::is_same<decltype(this), Nontemplate*>::value, "");
        static_assert(!std::is_same<decltype(this), Nontemplate* const&>::value, "");
        return this;
    }
};

template<typename T>
struct Template {
    auto f() -> decltype(this)
    {
        static_assert(std::is_same<decltype(this), Template<T>*>::value, "");
        static_assert(!std::is_same<decltype(this), Template<T>* const&>::value, "");
        return this;
    }
};

int main()
{
    Nontemplate().f();
    Template<int>().f();
}