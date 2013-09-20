#include <type_traits>
#include <vector>

template <typename T>
class Foo{
    double bar;
public:
    template<typename U=T, 
        class = typename std::enable_if<std::is_compound<U>::value>::type
        >
    Foo(typename T::value_type& b):bar(b){}

    template<typename U=T, 
        class = typename std::enable_if<!std::is_compound<U>::value>::type
        >
    Foo(T b):bar(b){}   
};

int main(){
    double d=1.0;
    Foo<std::vector<double>> f2(d); // works
    Foo<double> f1(d);          // compiler error
}