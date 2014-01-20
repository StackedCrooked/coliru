#include <iterator>
#include <utility>
#include <vector>

template <typename T> class bar;

template<typename Derived, typename ValType>
class foo
{
public:
    template<typename R>
    bar<typename std::vector<R>::const_iterator> select();
};

template<typename T>
class bar
    : public foo<bar<T>, typename std::iterator_traits<T>::value_type>
{
public:
    bar(std::vector<typename std::iterator_traits<T>::value_type>&& vec)
    {

    }
};

template <typename Derived, typename ValType>
template<typename R>
bar<typename std::vector<R>::const_iterator> foo<Derived, ValType>::select()
{
    std::vector<R> translation;
    return bar<typename std::vector<R>::const_iterator>(std::move(translation));
}
