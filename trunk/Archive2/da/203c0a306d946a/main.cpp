#include <iostream>
#include <string>
#include <vector>

class X{
protected:
    int stream(int) {}
};

template<bool b>
void show(){
    std::cout << b;
}

struct Y : public X{

/// Put this to define  . Replace "stream" with your function name
    template<class T, class retT, class ...Args>
    auto  test_function( int )  -> std::is_same<decltype(stream(std::declval<Args>()...)), retT>{
        return std::is_same<decltype(stream(std::declval<Args>()...)), retT>();
    }

    template<class , class, class ...Args>
    std::false_type test_function(long) {
        return std::false_type();
    }

    template<class T, class ...Args>
    auto has_stream( ) -> decltype( test_function<T, int, Args...>(0) ){
        return test_function<T, int, Args...>(0);
    }
/// END.    
    

    Y(){
        //show< has_stream<X, int>() >();
        std::cout << has_stream<Y, int>();
    }
};

       
int main()
{
    Y();    
    return 0;
}
