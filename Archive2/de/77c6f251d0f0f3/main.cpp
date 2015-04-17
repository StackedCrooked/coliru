#include <cstdint>
#include <iostream>

// Здесь компилятор может предполагать, что p64 и p32 никак не пересекаются
void f(int64_t* p64, int32_t* p32) {
    int val = *p64;
    std::cout << val << '\n';
    *p32 = 0; // Изменение значения может быть невидимым через указатель p64
    val = *p64; // Операция чтения может быть оптимизирована
    std::cout << val << '\n';
}

int main() {
    int64_t val = 1;
    f(&val, (int32_t*)&val);
}
