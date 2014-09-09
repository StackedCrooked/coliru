#include <iostream>
#include <vector>
#include <tuple>

template<size_t MIN, size_t MAX, typename T, typename H>
struct HANDLE_SINGLE_TUPLE_ELEMENT {
    static void handle(T t, H h) {
        h(std::get<MIN>(t));
        HANDLE_SINGLE_TUPLE_ELEMENT<MIN + 1, MAX, T, H>::handle(t, h);
    }
};

template<size_t MAX, typename T, typename H>
struct HANDLE_SINGLE_TUPLE_ELEMENT<MAX,MAX,T, H> {
    static void handle(T, H) {}
};


template<typename T, typename H>
void handle_tuple(T t, H h) {
    HANDLE_SINGLE_TUPLE_ELEMENT<0, std::tuple_size<T>::value, T, H>::handle(t, h);
}


struct COUT_HANDLER {
    template<typename T>
    void operator()(T t) {
        std::cout << t << std::endl;
    }
};

int main(int argc, const char * argv[])
{
    typedef std::tuple<int, double> t_int_double;
    
    std::cout << std::tuple_size<t_int_double>::value << std::endl;
    
    int i = 0;
    double d = 0.0;
    std::tie(i, d) = std::make_tuple(42,3.14159);
    std::cout << "i = " << i << std::endl; //print i = 42
    std::cout << "d = " << d << std::endl; //print d = 3.14159
    i *= 2; d*= 2.0;
    std::tuple<int, double> t = std::tie(i,d);
    std::cout << "get<0> = " << std::get<0>(t) << std::endl; //print get<0> = 84
    std::cout << "get<1> = " << std::get<1>(t) << std::endl; //print get<1> = 6.28318

#if __has_feature(cxx_generic_lambdas)
    std::cout << "GENERIC LAMBBDAS ARE SUPPORTED" << std::endl;
    handle_tuple(t, [] (auto t) {std::cout << t << std::endl;} );
#else
    std::cout << "GENERIC LAMBBDAS ARE NOT SUPPORTED" << std::endl;
    handle_tuple(t, COUT_HANDLER());
#endif
    std::vector<std::tuple<int,float>> v { {1,1.0}, {2,2.0} };
    std::tuple<int,double> t3 = {42,3.14};
    handle_tuple(t3, COUT_HANDLER());

    return 0;
}