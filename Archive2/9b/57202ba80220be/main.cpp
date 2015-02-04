#include <atomic>
#include <cstdint>
#include <type_traits>

extern void* aglujUnit;

struct Closure {
    void* type;
    void** freeVariables;
    std::uint64_t freeVariableCount;
    void* (*implementation)(Closure*, void* parameter);

    void* operator()(void* parameter) {
        return this->implementation(this, parameter);
    }
};

struct Lazy {
    void* type;
    void* value;
    Closure initializer;
};

void* force(Lazy* lazy) {
    auto value = __sync_fetch_and_add(&lazy->value, 0);
    if (value == nullptr) {
        value = lazy->initializer(aglujUnit);
        __sync_lock_test_and_set(&lazy->value, value);
    }
    return value;
}