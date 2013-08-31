namespace 
{
    template <typename F>
        void apply_to_each(F f) {}

    template <typename F, typename First, typename... More> 
        void apply_to_each(F f, First const& first, More const&... more)
        {
            f(first);
            apply_to_each(f, more...);
        }
}

/// demo
#include <iostream>

struct Foo
{
    template <typename T>
        void operator()(T const& t) const { 
            std::cout << t << "\n";
        }
};

int main()
{
    apply_to_each(Foo(), "hello", 42, "universe", "fwoop");
}

