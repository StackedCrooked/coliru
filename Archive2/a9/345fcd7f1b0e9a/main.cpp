#include <functional>
#include <type_traits>

template <typename L> void Callback(L l){
    using F = typename std::remove_pointer<decltype(+l)>::type;
    std::function<F> f( l );
    // store f and call later
}

int main(){
    Callback([](int a, float b){
        // do something
    });
}
