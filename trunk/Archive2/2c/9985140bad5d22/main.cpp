#include <memory>

void sink(std::unique_ptr<int>) {}

template<class T>
std::unique_ptr<T> make_unique() {return {};}

int main() {
    std::unique_ptr<int>&& ptr = make_unique<int>(); 
    sink(ptr);
}