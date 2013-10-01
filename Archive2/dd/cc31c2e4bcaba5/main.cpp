    #include <dlfcn.h>
     
    #include <functional>
    #include <iostream>
    #include <memory>
    #include <stdexcept>
    #include <string>
    #include <type_traits>
     
    // Keep-alive, fake Functor
    template<typename T>
    class DL_sym_fun {
    const T* f;
    std::shared_ptr<void> handle;
    public:
    DL_sym_fun(const T* f, const std::shared_ptr<void>& handle) : f(f), handle(handle) {}
     
    template<typename... Args>
    auto operator()(Args&&... args) {
    return (*f)(std::forward<Args>(args)...);
    }
    };
     
    // Keep-alive, fake Deleter
    class DL_sym_var {
    std::shared_ptr<void> handle;
    public:
    DL_sym_var(const std::shared_ptr<void>& handle) : handle(handle) {}
    void operator()(const void*) const noexcept {}
    };
     
    // Deleter for dlopen handles
    struct DL_close {
    void operator()(void* handle) const noexcept {
     
    std::cout << "dlclose(" << handle << ")\n";
    if (handle == nullptr) return;
     
    ::dlclose(handle);
    const char* r = ::dlerror();
    if (r) std::cerr << r << '\n';
    }
    };
     
    // Exception class
    class DL_error : public std::runtime_error {
    public:
    DL_error(const char* what) : std::runtime_error(what) {};
    };
     
    // Refcounted dlopen stuff
    class DL {
    std::shared_ptr<void> handle;
     
    template<typename T>
    T* _sym(const std::string& symbol) const {
    T* ptr;
    *reinterpret_cast<void**>(&ptr) = ::dlsym(handle.get(), symbol.c_str());
    const char* r = ::dlerror();
    if (r) throw DL_error(r);
    return ptr;
    }
     
    public:
    DL() : DL(nullptr) {}
    DL(const std::string& so) : DL(so.c_str()) {}
    DL(const char* so) : handle(::dlopen(so, RTLD_LAZY), DL_close()) {
    std::cout << "dlopen(\"" << so << "\") -> " << handle.get() << '\n';
    const char* r = ::dlerror();
    if (r) throw DL_error(r);
    }
     
    template<typename T, typename = typename std::enable_if<std::is_function<T>::value>::type>
    std::function<T> sym(const std::string& symbol) const {
    std::cout << "sym_fun(\"" << symbol << "\")\n";
    return DL_sym_fun<T>(_sym<T>(symbol), handle);
    }
     
    template<typename T, typename = typename std::enable_if<!std::is_function<T>::value>::type>
    std::unique_ptr<T,DL_sym_var> sym(const std::string& symbol) const {
    std::cout << "sym_fun(\"" << symbol << "\")\n";
    return std::unique_ptr<T,DL_sym_var>(_sym<T>(symbol), handle);
    }
    };
     
    //--
     
    #include <iostream>
     
    void Y() {
    std::function<double(double)> cos;
    {
    cos = DL("libm.so").sym<double(double)>("cos");
    }
    std::cout << "cos(2.0): " << cos(2.0) << '\n';
    }
     
    int main(int argc, char** argv) {
    Y();
     
    try {
    DL("barf.so");
    } catch(const std::exception& e) {
    std::cout << e.what() << "\n";
    }
     
    try {
    DL("libm.so").sym<void(void)>("barf");
    } catch(const std::exception& e) {
    std::cout << e.what() << "\n";
    }
     
    return 0;
    }