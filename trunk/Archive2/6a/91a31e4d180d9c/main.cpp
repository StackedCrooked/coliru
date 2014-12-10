#include <utility>

class Context {
    template<typename T>
    T construct();
};

template<typename T, typename ...Args>
struct aggregate {
    T construct(Context& ctx) {
        return { std::move(ctx.construct<Args>())... };
    }
};

typedef struct {
    float xyz[3];
} Vector3;

using ConstructVector = aggregate<Vector3, float[3]>;