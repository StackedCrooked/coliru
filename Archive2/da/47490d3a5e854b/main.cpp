declare {i32, i1} @llvm.uadd.with.overflow.i32(i32 %a, i32 %b)

declare void @mill_throw_overflow() noreturn

define i32 @mill_int32_add(i32 %a, i32 %b) {
    %res = call {i32, i1} @llvm.uadd.with.overflow.i32(i32 %a, i32 %b)
    %sum = extractvalue {i32, i1} %res, 0
    %obit = extractvalue {i32, i1} %res, 1
    br i1 %obit, label %error, label %normal
normal:
    ret i32 %sum
error:
    tail call void @mill_throw_overflow()
    unreachable
}

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>

extern "C" void mill_throw_overflow() {
    throw std::overflow_error("fuck");
}

extern "C" std::int32_t mill_int32_add(std::int32_t a, std::int32_t b);

int main() {
    std::cout << mill_int32_add(0, 1) << '\n';
    std::cout << mill_int32_add(1, 2) << '\n';
    std::cout << mill_int32_add(2, 3) << '\n';
    try {
        std::cout << mill_int32_add(std::numeric_limits<std::uint32_t>::max(), 1) << '\n';
    } catch (std::overflow_error const& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}