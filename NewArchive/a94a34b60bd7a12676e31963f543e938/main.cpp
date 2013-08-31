#include <memory>
#include <string>
#include <iostream>

namespace std {
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(args...));
    }
}

int main() {
   auto ptr = std::make_unique<std::string>("Hello world!");
   std::cout << *ptr << std::endl;
   return 0;
}