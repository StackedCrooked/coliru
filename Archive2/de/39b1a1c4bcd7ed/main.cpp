#include <vector>
#include <string>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>
#include <iostream>

template<typename ... T> class Node {};
template<typename ... T> class Link {};

std::string demangled(char const* tname) {
    std::unique_ptr<char, void(*)(void*)>
        name{abi::__cxa_demangle(tname, 0, 0, nullptr), std::free};
    return {name.get()};
}

#define THIS_CLASS_NAME() demangled(typeid(*this).name())

template <typename N, typename L>
class Network {
    std::vector<N> nodes;
    std::vector<L> links;
    
    public:
    Network() {
        std::cout << THIS_CLASS_NAME() << std::endl;
    }
};

int main() {
    Network<Node<int, int>, Link<std::string>> net;
    return 0;
}