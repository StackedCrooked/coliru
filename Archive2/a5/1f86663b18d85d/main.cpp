#include <vector>

template<typename T>
void call_destructor(T* x) {
    x->~T();
}

int main() {
    auto buffer = new char[sizeof(std::vector<int>::iterator)];
    
    auto iterator = new((void*)buffer) std::vector<int>::iterator();
    call_destructor(iterator);
    
    delete[] buffer;
}
