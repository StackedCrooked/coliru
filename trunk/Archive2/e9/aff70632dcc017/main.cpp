#include <atomic>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

#define AGLUJ_CHECK_TYPE(Type) \
    static_assert(std::is_standard_layout<Type>() && \
                  std::is_same<decltype(std::declval<Type>().type), void*>() && \
                  offsetof(Type, type) == 0, \
                  #Type " is fucked-up!")

namespace agluj {
    struct Closure {
        void* type;
        void** freeVariables;
        std::uint64_t freeVariableCount;
        void* (*implementation)(Closure const*, void* parameter);
    
        void* operator()(void* parameter) const {
            return implementation(this, parameter);
        }
    };
    AGLUJ_CHECK_TYPE(Closure);

    struct Lazy {
        void* type;
        void* value;
        Closure initializer;
    };
    AGLUJ_CHECK_TYPE(Lazy);

    void* force(Lazy* lazy, void* unit) {
        auto value = __sync_fetch_and_add(&lazy->value, 0);
        if (value == nullptr) {
            value = lazy->initializer(unit);
            __sync_lock_test_and_set(&lazy->value, value);
        }
        return value;
    }

    struct Ref {
        void* type;
        void* value;
    };
    AGLUJ_CHECK_TYPE(Ref);

    void* get(Ref* ref) {
        return __sync_fetch_and_add(&ref->value, 0);
    }

    void* set(Ref* ref, void* value) {
        return __sync_lock_test_and_set(&ref->value, value);
    }
}