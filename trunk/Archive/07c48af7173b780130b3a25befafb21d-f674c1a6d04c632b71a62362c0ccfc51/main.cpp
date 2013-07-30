#include <iostream>
#include <vector>

template<typename T>
struct Ref {
    Ref() {}
    
    template <typename R>
    inline Ref (const Ref<R> &other)
    {
        std::cerr << "copy ctor " << '\n';
    }
    
    template <typename R>
    inline Ref (Ref<R> &&other)
    {
        std::cerr << "move ctor " << '\n';
    }
};

    
int main() {
    std::vector<Ref<int>> s_stateStack;
    
    // Keep a reference so we don't free the state by mistake
    Ref<int> ref;

    std::cerr << "pre push " << '\n';
    s_stateStack.push_back(ref);
    std::cerr << "post push " << '\n';
}