#include <new> // for placement new
#include <utility> // for std::forward
#include <memory> // for std::addressof
#include <type_traits> // for std::aligned_storage_t

// construct an object in-place
template<typename T, typename... Args>
void construct(void* ptr, Args&&... args) {
    new(ptr) T(std::forward<Args>(args)...);
}

// destroy an object in-place
template<typename T, typename U>
void destroy(U* src) {
    static_cast<T*>(static_cast<void*>(src))->~T();
}

// type for an array of uninitialized storage
template<typename T, size_t N=1>
using uninitialized_buffer = std::aligned_storage_t<sizeof(T), alignof(T)>[N];

#include <iostream>

// some class with verbose special members
class tracked {
    static int next_id;
    int id{++next_id};
public:
    tracked() { std::cout << "tracked(" << id << ")\n"; }
    tracked(const tracked& other) { std::cout << "tracked(" << id << ", copy:" << other.id << ")\n"; }
    tracked(tracked& other) { std::cout << "tracked(" << id << ", move:" << other.id << ")\n"; }
    ~tracked() { std::cout << "~tracked(" << id << ")\n"; }
    tracked& operator=(const tracked& other) {
        std::cout << "tracked::operator=(" << id << ", copy:" << other.id << ")\n";
        return *this;
    }
    tracked& operator=(tracked&& other) {
        std::cout << "tracked::operator=(" << id << ", move:" << other.id << ")\n";
        return *this;
    }
    int get_id() const { return id; }
};


int main() {
    uninitialized_buffer<tracked, 2> buf;
    std::cout << "Creating buf doesn't invoke any constructors\n";
    std::cout << "Explicitly creating 2 objects\n";
    construct<tracked>(std::addressof(buf[0]));
    construct<tracked>(std::addressof(buf[1]));
    std::cout << "Explicitly destroying 2 object in the inverse order\n";
    destroy<tracked>(std::addressof(buf[0]));
    destroy<tracked>(std::addressof(buf[1]));
    std::cout << "Destroying buf doesn't invoke any destructors\n";
}

int tracked::next_id{};
