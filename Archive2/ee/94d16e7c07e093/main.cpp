#include <iostream>
#include <string>
#include <vector>

class X{
protected:
    int stream(int) const{}
};
struct Y : public X{


/// Put this tp define    
    template<class retT, class ...Args>
    constexpr bool  test_function( int ) const{
        return std::is_same<decltype(stream(std::declval<Args>()...)), retT>::value;
    }

    template<class , class ...Args>
    constexpr bool test_function(long) const{
        return false;
    }

    template<class T, class ...Args>
    constexpr bool has_stream( ) const{
        return test_function<int, Args...>(0);
    }
/// END.    
    

    Y(){
        std::cout << has_stream<X, int>();
    }
};

       
int main()
{
    Y();    
}
