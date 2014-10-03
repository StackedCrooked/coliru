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
        std::array<ffi_type*, sizeof...(Args) + 2> args;
        args.fill(&ffi_type_pointer);
        ffi_prep_cif(&cif, FFI_DEFAULT_ABI, args.size(), &ffi_type_void, args.data());

        auto closure = ffi_closure_alloc(sizeof(ffi_closure), reinterpret_cast<void**>(&thunk));
        ffi_prep_closure_loc(static_cast<ffi_closure*>(closure), &cif, &call, this, reinterpret_cast<void*>(thunk));
    }

    operator fptr_t() const {
        return thunk;
    }

private:
    static void call(ffi_cif*, void*, void** args, void* self_void) {
        auto self = static_cast<bound_function*>(self_void);
        self->template call_<0>(args);
    }

    template<std::size_t N, typename... CallArgs>
    typename std::enable_if<N != sizeof...(Args)>::type call_(void** args, CallArgs&&... callArgs) {
        call_<N + 1>(args, std::forward<CallArgs>(callArgs)..., *static_cast<int*>(args[N]));
    }

    template<std::size_t N, typename... CallArgs>
    typename std::enable_if<N == sizeof...(Args)>::type call_(void**, CallArgs&&... callArgs) {
        thunk(std::forward<CallArgs>(callArgs)...);
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
}

int main() {
    int x = 0;
    bound_function<int(int)> f([&] (int y) { return x += y; });
    crappy_c_api(f);
    return 0;
}
