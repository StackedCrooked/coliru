#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

struct A{int value;};

struct O{
    A value;
    template<typename Args>
    static void test2(Args &&args){
        std::cout << std::endl << "!!!" << std::is_rvalue_reference<decltype(args)>::value << std::endl;
    }
};


template<typename Args>
void test(Args &&args){
    using t = decltype(std::forward<Args>(args).value);
    std::cout << std::is_rvalue_reference<decltype(args)>::value;
    std::cout << std::is_rvalue_reference<decltype(std::forward<Args>(args).value)>::value;
    std::cout << std::is_rvalue_reference<t>::value;
    O::template test2< 
            t
        >(
        std::forward<t>(
            std::forward<Args>(args).value
        )
    );
}



       
int main()
{
    O o;
    test(o);
    
    return 0;
}
