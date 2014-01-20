#include <vector>
#include <string>

template<typename T>
class bar;

template<typename Derived, typename ValType>
class foo
{
public:
    template<typename R>
    bar<typename std::vector<R>::const_iterator> select()
    {
        std::vector<R> translation;

        return bar<typename std::vector<R>::const_iterator>(std::move(translation));
    }
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

int main()
{
    std::vector<int> enumerable_vector;
    enumerable_vector.push_back(1);
    enumerable_vector.push_back(2);

    bar<typename std::vector<int>::const_iterator> baz(std::move(enumerable_vector));
    baz.select<std::string>();
}
