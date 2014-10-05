#include <iostream>
#include <typeinfo>

template <bool B, typename TRUE, typename FALSE>
class if_then_else;

template <typename TRUE, typename FALSE>
class if_then_else<true, TRUE, FALSE> {
public:
    typedef TRUE type;
};

template <typename TRUE, typename FALSE>
class if_then_else<false, TRUE, FALSE> {
public:
    typedef FALSE type;
};


int main()
{
    if_then_else<true, int, float>::type t0_true = 5;
    if_then_else<false, int, float>::type t0_false = 5.0;
    
    std::cout << typeid(t0_true).name() << '\n';
    std::cout << typeid(t0_false).name() << '\n';

    return 0;
}
