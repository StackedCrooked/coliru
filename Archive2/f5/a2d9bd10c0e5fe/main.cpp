 #include <iostream>
 #include <array>
 #include <type_traits>
 
 template<typename T> extern size_t array_size;
 template<typename T, size_t N> 
 constexpr size_t array_size<T[N]> = N;
 
template<typename T, size_t N> 
constexpr size_t array_size<std::array<T, N>> = N;

 template<typename Buff>
 void func(Buff &buff) {   
    static_assert(array_size<Buff> >= 8, "array_size<Buff> >= 8");
}

//fucker works when out
char buff1[7];
std::array<char, 9> buff2;
 
int main() {
 
 func(buff1);
  func(buff2);
}