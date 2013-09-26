#include <cstddef>
#include <type_traits>

template<std::size_t N>
void foo(int(&)[N]) {   
}

int main() {
    static_assert(std::is_same<int[], int*>::value, "They're not the same.");
    
    int arr[5];
    int *p = arr;
    
    static_assert(sizeof arr == sizeof p, "Again, not the same.");
    
    foo(arr);
    
    p = new int[5];
    foo(p);
    delete[] p;
}