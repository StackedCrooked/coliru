#include <iostream>
#include <string>
#include <vector>

struct A{};
struct B{};

template<class T, class FieldT>
using addRefU = typename std::conditional<
                            false,
                            typename std::add_rvalue_reference< FieldT >::type,
                            typename std::conditional<
                                true,
                                typename std::add_rvalue_reference< FieldT >::type,
                                typename std::add_lvalue_reference< FieldT >::type
                            >::type
                        >::type;



int main()
{
        std::cout << std::is_rvalue_reference<
            addRefU<A, B>
        >::value << std::endl;
        std::cout << std::is_lvalue_reference<
            addRefU<A, B>
        >::value << std::endl;
        
}
