#include <memory>

void sink(std::unique_ptr<int>) {}

int main() {
    auto ptr = std::unique_ptr<int>(); 
    sink(ptr);
}