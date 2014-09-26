#include <cassert>
#include <iostream>
#include <type_traits>
#include <vector>
#include <typeinfo>

namespace onhands
{

template <typename T, typename U, typename V>
class unique_variant
{
    public:
        unique_variant();
        template <typename desiredType> desiredType& acquire();

    private:
        void*                           m_ptr;
        std::vector<std::type_info&>     types;
};

template <typename T, typename U, typename V> template <typename desiredType> desiredType& unique_variant<T,U,V>::acquire()
{
    if ( std::is_same<T,desiredType>::value || std::is_same<U,desiredType>::value || std::is_same<V,desiredType>::value )
    {
        std::cout << "yehey";
    }
    return *static_cast<desiredType*>(m_ptr);
}

template <typename T, typename U, typename V> unique_variant<T, U, V>::unique_variant()
{
    types.push_back(typeid(T));
    types.push_back(typeid(U));
    types.push_back(typeid(V));
}

// Implementation should go here.

}

class CustomClass
{
    int m_field;
public:
    CustomClass()
        : m_field(42)
    {
    }

    int getField() const { return m_field; }
};

int main(int, char **)
{
    onhands::unique_variant<int, float, ::CustomClass> variant;
    int & int_ = variant.acquire<int>();
    int_ = 1;
    int & otherInt = variant.acquire<int>();
    assert(int_ == otherInt && "Something's wrong");
    ::CustomClass & customClass = variant.acquire<::CustomClass>();
    //assert(42 == customClass.getField() && "Something's qwrong");
}
