extern "C" {
struct my_c_api;

typedef int(*callback)(void*, my_c_api*);
struct my_c_api {
    int x;
    void* data;
    callback cb;
};


void init_api(my_c_api* api) {
    api->x = 10;
    api->data = 0;
    api->cb = 0;
}

void add_callback(my_c_api* api, callback c, void* data) {
    api->cb = c;
    api->data = data;
}

void delete_callback(my_c_api* api, callback c, void* data) {
    if(api->cb == c && api->data == data) {
        api->cb = 0;
        api->data = 0;
    }
}

void do_api_stuff(my_c_api* api) {
    if(api && api->cb) {
        api->x = api->cb(api->data, api);
    }
}
}

template<typename T>
int do_callback(void* data, my_c_api* api) {
    auto* ptr = static_cast<T*>(data);
    return (*ptr)(*api);
}

template<typename Function>
void modern_callback(my_c_api* api, const Function& f) {
    add_callback(api, do_callback<Function>, static_cast<void*>(const_cast<Function*>(&f)));
}

template<typename Function>
void remove_callback(my_c_api* api, const Function& f) {
    delete_callback(api, do_callback<Function>, static_cast<void*>(const_cast<Function*>(&f)));
}

#include <iostream>

int main() {
    my_c_api api;
    init_api(&api);
    std::cout << api.x << '\n';
    modern_callback(&api, [](const my_c_api& api) { return api.x * 10; });
    do_api_stuff(&api);
    std::cout << api.x << '\n';
    do_api_stuff(&api);
    std::cout << api.x << '\n';
}
