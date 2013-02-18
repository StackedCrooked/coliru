#include <array>

constexpr std::size_t sum_chars(char const* p, std::size_t sum = 0){
    return *p == '\0' ? sum : *p + sum_chars(p+1);
}

int main(){
    std::array<int, sum_chars("hi")> a;
    (void)a;
}