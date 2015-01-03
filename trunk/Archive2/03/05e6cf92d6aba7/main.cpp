#include <vector>

template<typename T>
struct base {
    struct traits {
        template<typename U> using alias = std::vector<U>;
    };
};

template<typename T>
struct derived : base<T> {
    using traits = typename base<T>::traits;
    using usage_example = typename traits::template alias<T>;
};

int main()
{
    derived<int> d;
}