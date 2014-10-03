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

        auto closure = ffi_closure_alloc(sizeof(ffi_closure), &thunk);
        ffi_prep_closure_loc(closure, &cif, &call, this, thunk);
    }

    operator fptr_t() const {
        return thunk;
    }

private:
    static void call(ffi_cif, void*, void** args, void* self_void) {
        auto self = static_cast<bound_function*>(self_void);
        self->call_<0>(args);
    }

    template<std::size_t N>
    typename std::enable_if<N != sizeof...(Args)>::type call_(void** args) {
        call_<N + 1>(args);
    }

    template<std::size_t N>
    typename std::enable_if<N == sizeof...(Args)>::type call_(void** args) {
        (void)args;
    }

    std::function<Ret(Args...)> function;
    ffi_cif cif;
    fptr_t thunk;
};

int main() {
    return 0;
}
