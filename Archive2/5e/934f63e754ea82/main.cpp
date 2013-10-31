#include <functional>
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
        union {
            R (bound_function::*mptr)(Args...);
            struct {
                R(*impl)(bound_function*, Args...);
                bound_function* self;
            } foo;
        };
        
        mptr = &call;
        
        auto data = mmap(nullptr, 512, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
        
        unsigned char bytes[] = {
            0xFF
        };
        
        memcpy(data, bytes, sizeof(bytes));
        
        auto f = reinterpret_cast<R(*)(Args...)>(data);

        return f;
    }

private:
    R call(Args... args) {
        return function(args...);
    }
    
    std::function<R(Args...)> function;
};

int main() {
    
}
