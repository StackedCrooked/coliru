#include <iostream>
#include <dlfcn.h>

void* handle;

template<class func_sig> func_sig get_func(const char* signature)
{
    dlerror();
    func_sig func = (func_sig) dlsym(handle, __FUNCDNAME__);
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "dlsym error: " << dlsym_error << '\n';
        dlclose(handle);
        exit(1);
    }
    return func;
}

void say(int a) {
    typedef void(*func_sig)(int);
    static func_sig func = get_func<func_sig>(__FUNCDNAME__);
    return func(a);
}

void say(float a) {
    typedef void(*func_sig)(float);
    static func_sig func = get_func<func_sig>(__FUNCDNAME__);
    return func(a);
}

int main() {
    // open library
    //void* handle = dlopen("./say_externC.so", RTLD_LAZY);
    handle = dlopen("./say.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen error: " << dlerror() << '\n';
        return 1;
    }

    // use function
    int myint = 3;
    say(myint);
    float myfloat = 5.0f;
    say(myfloat);

    // close library
    dlclose(handle);
}