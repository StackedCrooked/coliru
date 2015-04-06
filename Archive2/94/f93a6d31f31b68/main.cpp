#include <boost/core/demangle.hpp>
#include <execinfo.h>
#include <string>
#include <vector>

class with_stack_trace {
public:
    std::vector<std::string> const& stack_trace() const {
        return entries;
    }

protected:
    with_stack_trace() {
        std::vector<void*> buffer(4);
        int n;
        while ((n = backtrace(buffer.data(), buffer.size())) == static_cast<int>(buffer.size())) {
            buffer.resize(buffer.size() * 2);
        }
        auto symbols = backtrace_symbols(buffer.data(), n);
        for (int i = 2; i < n; ++i) {
            std::string line = symbols[i];
            auto from = line.find('(');
            auto to = line.find('+');
            if (from != std::string::npos && to != std::string::npos) {
                auto mangled_name = line.substr(from + 1, to - 1 - from);
                auto demangled_name = boost::core::demangle(mangled_name.c_str());
                line.replace(from + 1, to - 1 - from, demangled_name.c_str(), demangled_name.size());
            }
            entries.emplace_back(line);
        }
    }

private:
    std::vector<std::string> entries;
};

// example:
#include <iostream>
#include <stdexcept>

class my_exception : public std::runtime_error, public virtual with_stack_trace {
public:
    using std::runtime_error::runtime_error;
};

void g() {
    throw my_exception("oops!");
}

void f() {
    g();
}

int main() {
    try {
        f();
    } catch (my_exception const& ex) {
        std::cerr << ex.what() << '\n';
        for (auto&& entry : ex.stack_trace()) {
            std::cerr << "  " << entry << '\n';
        }
    }
    return 0;
}