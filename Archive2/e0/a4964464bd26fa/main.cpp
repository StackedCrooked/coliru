#include <cstdlib>
#include <iostream>
#include <mutex>

struct my_type {
    my_type() {std::cout << "Construct: " << this << "\n";}
    ~my_type() {std::cout << "Destroy: " << this << "\n";}
};

my_type const& instantiate() {
    struct empty {};
    union storage_t {
        empty e;
        my_type instance;
        constexpr storage_t() : e{} {}
        ~storage_t() {}
    };
    
    static std::once_flag flag;
    static storage_t storage;

    std::call_once(flag, []{
        ::new (&storage.instance) my_type;
        std::atexit([]{
            storage.instance.~my_type();
        }); 
    });

    return storage.instance;
}

int main() {
    std::cout << "Enter main\n";
    instantiate();
    std::cout << "Leave main\n";
}
