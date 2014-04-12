#include <iostream>

template <typename X, typename T>
struct basic_inner
{
    template <typename T2>
    basic_inner& operator=(const basic_inner<X, T2>&)
    {
        std::cout << "oi!\n";
        // do something...
        return *this;
    }
};

template <typename T>
struct outer
{
    template <typename X>
    struct inner : public basic_inner<X, T>
    {
        using basic_inner<X,T>::operator=;
        inner& operator=(const basic_inner<X, T> &that)
        {
            std::cout << "hm...\n";
            static_cast<basic_inner<X, T>&>(*this) = that;
            return *this;
        }
    };
};

template <>
struct outer<int>
{
    template <typename X>
    struct inner : public basic_inner<X, int>
    {
        inner& operator=(const basic_inner<X, int> &that)
        {
            std::cout << "wtf...";
            static_cast<basic_inner<X, int>&>(*this) = that;
            return *this;
        }
    };
};

int main()
{
    outer<double>::inner<void> x1;
    outer<int>::inner<void> x2;
    
    x1 = x2;
}