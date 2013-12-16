#include <vector>
#include <iostream>
#include <tuple>
#include <functional>

using namespace std;

tuple<int, string> foo() { 
    return make_tuple(5, "nothing");
}

tuple<int, int> foo(int a) {
    return make_tuple(5, a);
}


typedef decltype(foo(5)) FRet;

template<typename T>
struct is_tuple {
    typedef false_type value;
};

template<typename... T>
struct is_tuple<tuple<T...>> {
    typedef true_type value;
};


int main()
{
    static_assert(
        is_same<is_tuple<FRet>::value, true_type>::value,
        "FRet is not a tuple type"
    );
    
    
}