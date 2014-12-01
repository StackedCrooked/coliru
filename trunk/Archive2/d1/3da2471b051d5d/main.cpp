#include <iostream>
#include <vector>
#include <memory>
#include <type_traits>

void frobnicate(const uint8_t* raw_memory, size_t bytes){}

template <typename T, typename U>
T sized_ptr_cast(U p) {
    static_assert(std::is_pointer<T>::value, "");
    static_assert(std::is_pointer<U>::value, "");
    static_assert(sizeof(typename std::remove_pointer<T>::type) == sizeof(typename std::remove_pointer<U>::type), "size must be same");
    return reinterpret_cast<T>(p);
}

int main()
{
   std::vector<int> iv;
    std::vector<char> cv;
    
    frobnicate(sized_ptr_cast<const uint8_t*>(iv.data()), iv.size()); // must not compile
    frobnicate(sized_ptr_cast<const uint8_t*>(cv.data()), cv.size()); // should compile
}