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

    operator alias<R(*)(Args...)>() {
        auto data = static_cast<char*>(mmap(nullptr, 512, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0));
        
        unsigned char bytes[] = {
            0xB0 + 7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xB0 + 6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0b1111010,
        };
        
        static_assert(sizeof(this) == 8, "well, fuck");
        auto self = this;
        std::memcpy(data + 1, &self, 8);
        std::memcpy(data + 10, reinterpret_cast<void*>(&call), 8);
        
        std::memcpy(data, bytes, sizeof(bytes));
        
        auto f = reinterpret_cast<R(*)(Args...)>(data);

        return f;
    }

private:
    static R call(Args... args) {
        bound_function* self = nullptr;
        asm("movq %%r15, %0" : "=r"(self) : :);
        return self->function(args...);
    }
    
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