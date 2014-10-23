#include <memory>

void f(void* p) {}

template<class... T>
void g(T&&... t) {
    return f(std::forward<T>(t)...);
}

int main(int argc, char** argv) {
    f(0);
    g(0);
    
    return 0;
}