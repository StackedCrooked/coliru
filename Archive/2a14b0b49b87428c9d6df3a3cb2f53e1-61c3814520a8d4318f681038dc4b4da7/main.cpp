#include <boost/exception/all.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

template<typename T>
std::string demangle() noexcept /* terminate on throw (fair deal) */ {
    int st;
    char * const p = abi::__cxa_demangle(typeid(T).name(), 0, 0, &st);
    switch (st) {
        case 0: return std::unique_ptr<char, decltype(&std::free)>(p, std::free).get();
        case -1: assert(!"A memory allocation failure occurred."); // no memory = game over
        case -2: assert(!"Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: assert(!"One of the arguments is invalid.");
        default: assert(!"Unexpected demangle status");
    }        
}

struct general_exception : virtual std::exception, virtual boost::exception {
    // implicit move for the 'name' argument? or a copy?
    general_exception(std::string name) : std::exception(), name_(name)  {}
    virtual ~general_exception() throw() {}
    virtual const char* what() const noexcept { return name_.c_str(); }
    std::string name_;
};

template<typename T>
struct concrete_exception : virtual general_exception {
    concrete_exception() : general_exception(demangle<T>()) {}
    virtual ~concrete_exception() throw() {}
};

namespace filesystem {    
    namespace detail {
        void move_file_impl(const std::string & , const std::string &) { /*...*/}
    }
    
    bool exists(const std::string &) {
        return false;
    }
    
    struct file_not_found{};
    
    void move_file(const std::string & from, const std::string & to) {
        if (!exists(from)) {
            throw concrete_exception<file_not_found>() << boost::errinfo_file_name(from);
        }        
        detail::move_file_impl(from, to);
    }
}

int main() {
    try {
        filesystem::move_file("i_dont_exist.txt", "i_dont_matter.txt");
    }
    catch (const std::exception & exc) {
        if (exc.what() == demangle<filesystem::file_not_found>()) {
            if (auto * info = boost::get_error_info<boost::errinfo_file_name>(exc)) {
                std::cerr << "Caught: " << exc.what() << ". Detail: " << *info << std::endl;
            }
        }
    }
}