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
        auto data = mmap(nullptr, 512, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
        
        unsigned char bytes[] = {
            0xB0 + 7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xFF, 0b11111111,
        };
        
        static_assert(sizeof(this) == 8, "well, fuck");
        std::memcpy(data + 1, this, 8);
        
        std::memcpy(data, bytes, sizeof(bytes));
        
        auto f = reinterpret_cast<R(*)(Args...)>(data);

        return f;
    }

private:
    static R call(bound_function* self, Args... args) {
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
