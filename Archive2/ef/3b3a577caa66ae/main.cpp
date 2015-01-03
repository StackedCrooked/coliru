#include <map>
#include <utility>
#include <vector>

template<typename T>
struct base {
    template<typename X>
    using alias = std::vector<X>;
};

template<typename T, typename U>
struct base< std::pair<T, U> > {
    template<typename X, typename Y>
    using alias = std::map<X, Y>;
};

template<>
struct base<void>
{
    using alias = void;
};

template<typename T>
struct derived : base<T>
{
    // using base<T>::alias;  // <-- template or not? how many template-parameters?
};

int main() {}