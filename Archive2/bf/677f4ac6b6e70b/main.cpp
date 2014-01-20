#include <atomic>
#include <cstdlib>
#include <iostream>
#include <mutex>

struct my_type {
    my_type() {std::cout << "Construct: " << this << "\n";}
    ~my_type() {std::cout << "Destroy: " << this << "\n";}
};

my_type const& instantiate() {
    static typename std::aligned_storage<
      sizeof(my_type), alignof(my_type)
    >::type storage;
    static std::atomic<int> flag;

    while (flag < 2) {
        // all threads spin until the object is properly initialized
        int expected = 0;
        if (flag.compare_exchange_weak(expected, 1)) {
            // only one thread succeeds at the compare_exchange.
            try {
                ::new (&storage) my_type;
            } catch(...) {
                // Initialization failed. Let another thread try.
                flag = 0;
                throw;
            }
            // Success!
            std::atexit([] {
                reinterpret_cast<my_type&>(storage).~my_type();
            }); 
            flag = 2;
            break;
        }
    }

    return reinterpret_cast<my_type&>(storage);
}

int main() {
    std::cout << "Enter main\n";
    instantiate();
    std::cout << "Leave main\n";
}
