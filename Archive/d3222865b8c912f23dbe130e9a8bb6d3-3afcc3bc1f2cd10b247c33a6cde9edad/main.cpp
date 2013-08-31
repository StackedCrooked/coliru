#include <functional>

#define __stdcall //otherwise undefined

extern "C" void foo(int(__stdcall *callback)()) {
    callback();
}

namespace detail {
    std::function<int()> callback;
    
    extern "C" int __stdcall proxyCallback() {
        //possible additional processing
        return callback();
    }
}

template<typename F>
void wrappedFoo(F f) {
    detail::callback = f;
    foo(detail::proxyCallback);
}

int main() {
    wrappedFoo([&]() -> int {
        return 5;
    });   
}