#include <functional>

namespace legacy {

template<class T>
class Container
{
public:
};

} // namespace legacy

template < typename T >
legacy::Container<T>* begin(legacy::Container<T>&);

namespace adl {

template<class C> 
auto adl_begin(C && c) -> decltype(begin(std::forward<C>(c)))
{ 
    using std::begin;
    return begin(std::forward<C>(c)); // try to find non-member, fall back on std::
}

// similary for end()

} // namespace adl



using adl::adl_begin;

// print.h

int main()
{
    legacy::Container<int> c;
    auto x = adl_begin(c);
}
