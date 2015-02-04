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
static_assert(std::is_standard_layout<Closure>(), "Closure must be standard-layout!");

struct Lazy {
    void* type;
    void* value;
    Closure initializer;
};
static_assert(std::is_standard_layout<Lazy>(), "Lazy must be standard-layout!");

struct Ref {
    void* type;
    void* value;
};
static_assert(std::is_standard_layout<Ref>(), "Ref must be standard-layout!");

void* force(Lazy* lazy) {
    auto value = __sync_fetch_and_add(&lazy->value, 0);
    if (value == nullptr) {
        value = lazy->initializer(aglujUnit);
        __sync_lock_test_and_set(&lazy->value, value);
    }
    return value;
}

void* get(Ref* ref) {
    return __sync_fetch_and_add(&ref->value, 0);
}

void* set(Ref* ref, void* value) {
    return __sync_lock_test_and_set(&ref->value, value);
}