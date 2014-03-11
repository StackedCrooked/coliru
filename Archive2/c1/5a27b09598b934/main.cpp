#include <iostream>
#include <type_traits>

#include <array>

constexpr std::size_t fak(std::size_t n) {
    std::size_t result=1;
    while (n>0)
        result*=n--;
    return result;
}

constexpr std::array<std::size_t, 4> fak2() {
    std::size_t a[4]={0,0,0,0};
    a[0]=1;
    for (std::size_t i=1; i!=4; ++i)
        a[i]=i*a[i-1];
    return {{a[0], a[1], a[2], a[3]}};        
}


constexpr auto a=fak2();

int main() {
    using t=std::integral_constant<std::size_t, fak(7)>;
    
    using f0=std::integral_constant<std::size_t, a[0]>;
    using f1=std::integral_constant<std::size_t, a[1]>;
    using f2=std::integral_constant<std::size_t, a[2]>;
    using f3=std::integral_constant<std::size_t, a[3]>;
    
    std::cout << f0{} << " " << f1{} << f2{} << f3{} << std::endl; 
}