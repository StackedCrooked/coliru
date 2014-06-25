#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<class T, class FieldT>
using addRefU = typename std::conditional<
                            std::is_rvalue_reference<T>::value,
                            typename std::add_rvalue_reference< FieldT >::type,
                            typename std::conditional<
                                std::is_rvalue_reference<FieldT>::value,
                                typename std::add_rvalue_reference< FieldT >::type,
                                typename std::add_lvalue_reference< FieldT >::type
                            >::type
                        >::type;


struct A{int value;};

struct O{
    A value;
    template<typename Args>
    static void test2(Args &&args){
        std::cout << std::endl << "!!!" << std::is_rvalue_reference<decltype(args)>::value << std::endl;
    }
};

struct O2{
    O2(A &&value) : value(std::forward<A>(value)){}

    A &&value;
    template<typename Args>
    static void test2(Args &&args){
        std::cout << std::endl << "!!!" << std::is_rvalue_reference<decltype(args)>::value << std::endl;
    }
};


template<typename Args>
void test(Args &&args){
    std::cout <<"Argument rvalue: "<< std::is_rvalue_reference<decltype(args)>::value << std::endl;
    std::cout <<"Underlying type rvalue: "<< std::is_rvalue_reference<decltype(args.value)>::value << std::endl;
    
    using t = addRefU<decltype(args), decltype(args.value)>;
    std::cout << "deducted reference rvalue: " << std::is_rvalue_reference<t>::value << std::endl;
    
    O::template test2<t>(
        static_cast<t>(args.value)
    );
}



       
int main()
{
    O o;
    test(o);
    
    std::cout << "-----------------------" << std::endl;
    test(O());
    
    std::cout << "-----------------------" << std::endl;
    O2 o2{A()};
    test(o2);
    
    std::cout << "-----------------------" << std::endl;
    test(O2(A()));
    
    return 0;
}
