#include <iostream>

int main() {
    using fp_t = void(*)();
    void* vn = nullptr;
    fp_t foo = reinterpret_cast<fp_t>(vn); // GCC: warning, Clang: silence
    //fp_t foo = reinterpret_cast<fp_t>(nullptr); // error (GCC and Clang!)
    std::cout << !!foo << std::endl;
}
