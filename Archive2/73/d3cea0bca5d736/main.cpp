#include <iostream>

struct MoveMe
{
    MoveMe() {}
    MoveMe(MoveMe&&) { std::cout << "moved\n"; }
    MoveMe(const MoveMe&) { std::cout << "copied\n"; }
    MoveMe& operator=(const MoveMe&) { std::cout << "copy assigned\n"; return *this; }
    MoveMe& operator=( MoveMe&&) { std::cout << "move assigned\n"; return *this; }
};

template<typename T>
struct container {
    T value;
    using value_type = T;
    container() { }
    
public:
    T& operator[](int index) & { return value; }       // for lvalue objects
    T&& operator[](int index) && { return std::move(value); }     // for rvalue objects
};


template<typename T>
void test(container<T>&& rv_container)
{
    auto  m1 = rv_container[0];
    auto& m2 = rv_container[0];
    
    auto  m3 = container<T>()[0];
    auto& m4 = container<T>()[0];
}

int main()
{
    container<MoveMe> c;
    test(std::move(c));
}
