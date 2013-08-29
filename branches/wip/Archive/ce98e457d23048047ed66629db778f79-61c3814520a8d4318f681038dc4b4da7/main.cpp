#include <iostream>
#include <memory>
template<typename T, typename deleter, deleter d, T null_value = T {}> struct value_deleter {
    struct wrapper {
        T value;
        wrapper(T t) : value(t) {}
        bool operator==(std::nullptr_t) { return value == null_value; }
        bool operator!=(std::nullptr_t) { return value != null_value; }
        T operator*() { return value; }
        wrapper(std::nullptr_t) : value(null_value) {}
        wrapper() : value(null_value) {}
    };
    typedef wrapper pointer;
    void operator()(wrapper w) {
        if (w.value != null_value) {
            d(w.value);
        }
    }
};

void delete_my_int_handle(int h) {
    std::cout << "Getting rid of " << h << "\n";
}

int main() {
    std::unique_ptr<int, value_deleter<int, decltype(&delete_my_int_handle), &delete_my_int_handle>> myinthandle(200);
}