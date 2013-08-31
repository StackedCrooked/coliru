#include <cstddef>

bool fast_or_ptr(void *p, void *q) {
    return bool(reinterpret_cast<size_t>(p) | reinterpret_cast<size_t>(q));
}

bool slow_or_ptr(void *p, void *q) {
    return p || q;
}