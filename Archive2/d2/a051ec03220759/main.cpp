#include <cstdlib>
#include <iostream>
#include <mutex>

struct my_type {
    my_type() {std::cout << "Construct: " << this << "\n";}
    ~my_type() {std::cout << "Destroy: " << this << "\n";}
};

my_type const& instantiate() {
    static std::once_flag flag;
    static std::aligned_storage<sizeof(my_type), alignof(my_type)>::type storage;

    std::call_once(flag, []{
        ::new (&storage) my_type;
        std::atexit([]{ reinterpret_cast<my_type&>(storage).~my_type(); }); 
    });

    return reinterpret_cast<my_type&>(storage);
}

int main() {
    std::cout << "Enter main\n";
    instantiate();
    std::cout << "Leave main\n";
}
