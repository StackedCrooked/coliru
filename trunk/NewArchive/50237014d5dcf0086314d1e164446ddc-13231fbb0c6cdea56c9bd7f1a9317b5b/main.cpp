#include <iostream>
#include <cxxabi.h>
#include <memory>
#include <string>

void fail(char const* message) {
    throw std::logic_error(message);
}

std::string demangled(std::string const& sym) try {
    int status;
    std::unique_ptr<char, void(*)(void*)>
        name{abi::__cxa_demangle(sym.c_str(), nullptr, nullptr, &status), std::free};
    switch (status) {
        case -1: fail("A memory allocation failed");
        case -2: fail("mangled_name is not a valid name under the C++ ABI mangling rules");
        case -3: fail("One of the arguments is invalid");
    }
    return {name.get()};
} catch (std::logic_error& e) {
    std::cerr << "[ERROR] " << e.what() << '\n';
    return sym;
}

int main() {
    std::string sym;
    while (getline(std::cin, sym))
        std::cout << sym << '\t' << demangled(sym) << '\n';
}