define i32 @mill_int32_add(i32 %a, i32 %b) {
    %result = add i32 %a, %b
    ret i32 %result
}

define i32 @mill_int32_sub(i32 %a, i32 %b) {
    %result = sub i32 %a, %b
    ret i32 %result
}

#include <cstdint>
#include <iostream>
#include <limits>

extern "C" std::int32_t mill_int32_add(std::int32_t a, std::int32_t b);
extern "C" std::int32_t mill_int32_sub(std::int32_t a, std::int32_t b);

int main() {
    std::cout << mill_int32_add(std::numeric_limits<std::int32_t>::max(), 1) << '\n';
    std::cout << mill_int32_sub(std::numeric_limits<std::int32_t>::min(), 1) << '\n';
    return 0;
}