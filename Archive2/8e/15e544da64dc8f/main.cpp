#include <iostream> 
#include <functional> 

namespace std {
template <typename T>
using add_pointer_t = typename add_pointer<T>::type;
}
using CallType = std::add_pointer_t<void()>;

using FuncType = std::function<void()>;

int main() {
    std::cout << sizeof(CallType) << " " << sizeof(FuncType);
}