#include <functional>
#include <new>

int main() {
    typedef void*(*newptr_type)(std::size_t);
    
    auto fn = std::bind<void*>(newptr_type(::operator new), sizeof(char)*100);

    auto field = (char*)fn();
}