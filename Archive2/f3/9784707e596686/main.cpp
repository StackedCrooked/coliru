#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <new>
#include <sys/mman.h>

template<typename Sig, typename F>
class bound_function;
template<typename R, typename... Args, typename F>
class bound_function<R(Args...), F> {
private:
    using fptr_t = R(*)(Args...);

public:
    bound_function(F function_) : function(std::move(function_)) {
        // FIXME: Fix memory leak.
        thunk = static_cast<unsigned char*>(::mmap(nullptr, thunk_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0));
        if (thunk == MAP_FAILED) {
            throw std::bad_alloc();
        }
        std::memcpy(thunk, reinterpret_cast<void*>(&call), thunk_size);

        unsigned char magic_buf[8];
        auto magic_var = magic;
        std::memcpy(magic_buf, &magic_var, 8);

        auto it = std::search(thunk, thunk + thunk_size, magic_buf, magic_buf + 8);
        auto self = this;
        std::memcpy(it, &self, 8);
    }

    operator fptr_t() {
        return reinterpret_cast<R(*)(Args...)>(thunk);
    }

private:
    static std::uint64_t constexpr magic = std::numeric_limits<std::uint64_t>::max();
    static std::size_t constexpr thunk_size = 512;

    static R call(Args... args) {
        auto self = reinterpret_cast<bound_function*>(magic);
        return self->function(std::move(args)...);
    }

    F function;
    unsigned char* thunk;
};

template<typename Sig, typename F>
bound_function<Sig, F> make_bound_function(F function) {
    return bound_function<Sig, F>(std::move(function));
}

int call_back(int(*function)(int), int x) {
    return function(x);
}

int main() {
    int x = 0;
    auto function = make_bound_function<int(int)>([&] (int y) { return x += y; });

    call_back(function, 1) == 1;
    call_back(function, 2) == 3;
    call_back(function, 3) == 6;
    call_back(function, 4) == 10;

    return 0;
}
