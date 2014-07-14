#include <iostream>
#include <string>
#include <vector>

class X{
protected:
    int stream(int) const{return 7;}
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
        int x[1+has_stream<X, int>()] = {0};
        std::cout << has_stream<X, int>() <<"\n";
        for (auto&& i:x)
            std::cout << i << "\n";
    }
};

       
int main()
{
    Y();    
}
