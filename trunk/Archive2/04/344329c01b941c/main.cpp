#include <functional>
#include <utility>

template<class T, class V, class P>
struct checker{
    T value;
    V other;
    
    explicit operator bool() const{
        return P{}(value, other);
    }
};

template<class T, class V>
checker<T, V, std::not_equal_to<T>> unequal(T&& t, V&& v)
{
    return { std::forward<T>(t), std::forward<V>(v) };
}

#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

int main(){
    std::string s1 = "(abc)", s2 = "(abc";
    std::string target;
    if(auto check = unequal(s1.find(')'), s1.npos))
        std::copy(s1.begin(), s1.begin() + check.value, std::back_inserter(target));
    std::cout << target;
}
