#include <type_traits>

struct selfie_taker {
    void const* operator()() const {
        return this; // haha, clearly not stateless
    }
};

static_assert(std::is_empty<selfie_taker>::value, "it is however, empty");

struct i_can_make_it_worse {
    int operator()() const {
        static int x = 0;
        return ++x;
    }
};

static_assert(std::is_empty<i_can_make_it_worse>::value, "also empty");

int main() {}