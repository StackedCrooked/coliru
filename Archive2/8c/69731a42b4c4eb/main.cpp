#include <cstring>
#include <functional>
#include <iostream>
#include <sys/mman.h>

template<typename T>
using alias = T;

template<typename R, typename... Args>
class bound_function {
public:
    template<typename F>
    explicit bound_function(F function_) : function(function_) {

    }

#pragma GCC push_options
#pragma GCC optimize ("-O0")
    operator alias<R(*)(Args...)>() {
        unsigned char bytes[] = {
            0b01001001, 0xB8 + 7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0b01001001, 0xB8 + 6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0b11100110,
        };
        
        auto data = static_cast<char*>(mmap(nullptr, sizeof(bytes), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0));
        
        std::memcpy(data, bytes, sizeof(bytes));
        
        static_assert(sizeof(this) == 8, "well, fuck");
        auto self = this;
        std::memcpy(data + 2, &self, 8);
        std::memcpy(data + 12, reinterpret_cast<void*>(&call), 8);
        
        auto f = reinterpret_cast<R(*)(Args...)>(data);

        return f;
    }
#pragma GCC pop_options

private:
#pragma GCC push_options
#pragma GCC optimize ("-O0")
    static R call(Args... args) {
        bound_function* self = nullptr;
        asm volatile("movq %%r15, %0" : "=r"(self) : :);
        return self->function(args...);
    }
#pragma GCC pop_options
    
    std::function<R(Args...)> function;
};

void call_back(void(*f)()) {
    f();
}

int main() {
    int x = 0;

    bound_function<void> bf([&] {
        std::cout << "Hello, world!\n";
        std::cout << "x = " << x++ << "!\n";
    });

    for (auto i = 0; i < 10; ++i) {
        call_back(bf);
    }
}
