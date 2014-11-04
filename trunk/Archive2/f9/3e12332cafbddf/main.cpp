#include <iostream>
#include <iomanip>
#include <limits>


template <typename L, typename R>
void compare(L a, R b){
    static_assert(!std::numeric_limits<R>::is_signed, "");
    static_assert(std::numeric_limits<R>::max() >= std::numeric_limits<L>::max(), "");
    if ((a > 0) && (static_cast<R>(a) > b))
        std::cout << "a>b" << std::endl;
    else
        std::cout << "a<b" << std::endl;
}

int main(){
    
    
    int a = 2;
    unsigned int b = 3;
    
    compare(a, b);
        
    a = -2;
    b =  3;

    compare(a, b);   
        
        
    return 0;
}
