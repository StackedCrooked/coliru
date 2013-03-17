#include <type_traits>

template<class T> using Alias = T;

int main(){
    auto&& arr = Alias<int[]>{1,2,3};
    static_assert(std::is_same<decltype(arr), int(&&)[3]>::value, "...");
}