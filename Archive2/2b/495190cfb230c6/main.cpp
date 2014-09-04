#include <iostream>

struct my_api_t { int member; };

using callback_t = int(*)(my_api_t*, void*);

int eat_callback(callback_t callback, void* data) {
    my_api_t x;
    x.member = 10;
    return callback(&x, data);
}

template<typename Function>
int do_callback(my_api_t* stuff, void* data) {
    auto&& cb = *static_cast<Function*>(data);
    return cb(*stuff);
}

template<typename Function>
int modern_callback(Function f) {
    return eat_callback(do_callback<Function>, static_cast<void*>(&f));
}

int main() {
    std::cout <<
    modern_callback([](my_api_t& stuff) {
        return stuff.member > 10 ? 11 : 20;
    });
}
