#include <iostream>

#define VARGS_(_10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N 
#define VARGS(...) VARGS_(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)
    
#define MACRO_2(a, b) std::cout << a << ' ' << b;

#define MACRO_1(a) MACRO_2(a, "test") // Supply default argument

#define MACRO(...) CONCAT(MACRO_, VARGS(__VA_ARGS__))(__VA_ARGS__)

int main()
{
    MACRO(1);
}