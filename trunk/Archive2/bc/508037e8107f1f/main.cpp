#include <array>
#include <cstddef>
#include <ffi.h>
#include <functional>
#include <type_traits>
#include <utility>

template<typename Signature>
class bound_function;

template<typename Ret, typename... Args>
class bound_function<Ret(Args...)> {
    using fptr_t = Ret(*)(Args...);
public:
    template<typename F>
    explicit bound_function(F function_) : function(std::move(function_)) {
        std::array<ffi_type*, sizeof...(Args)> args;
        args.fill(&ffi_type_sint);
        ffi_prep_cif(&cif, FFI_DEFAULT_ABI, args.size(), &ffi_type_sint, args.data());

        auto closure = ffi_closure_alloc(sizeof(ffi_closure), reinterpret_cast<void**>(&thunk));
        ffi_prep_closure_loc(static_cast<ffi_closure*>(closure), &cif, &call, this, reinterpret_cast<void*>(thunk));
    }

    operator fptr_t() const {
        return thunk;
    }

private:
    static void call(ffi_cif*, void* ret, void** args, void* self_void) {
        auto self = static_cast<bound_function*>(self_void);
        *static_cast<Ret*>(ret) = self->template call_<0>(args);
    }

    template<std::size_t N, typename... CallArgs>
    typename std::enable_if<N != sizeof...(Args), Ret>::type call_(void** args, CallArgs... callArgs) {
        return call_<N + 1>(args, callArgs..., *static_cast<int*>(args[N]));
    }

    template<std::size_t N, typename... CallArgs>
    typename std::enable_if<N == sizeof...(Args), Ret>::type call_(void**, CallArgs... callArgs) {
        return function(callArgs...);
    }

    std::function<Ret(Args...)> function;
    ffi_cif cif;
    fptr_t thunk;
};

#include <iostream>

void crappy_c_api(int(*f)(int)) {
    std::cout << f(1) << '\n';
    std::cout << f(2) << '\n';
    std::cout << f(3) << '\n';
    std::cout << f(4) << '\n';
    std::cout << f(5) << '\n';
    std::cout << f(6) << '\n';
}

int main() {
    int x = 0;
    bound_function<int(int)> f([&] (int y) { return x += y; });
    crappy_c_api(f);
    return 0;
}
