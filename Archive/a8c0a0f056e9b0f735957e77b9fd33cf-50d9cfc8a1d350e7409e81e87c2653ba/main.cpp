template<typename T>
using result = typename T::result_type;
template<typename F, typename... Args>
result<F> void foo(Args&&... args)
#include <iostream>
 
int main() {
}