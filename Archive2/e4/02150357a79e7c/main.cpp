#include <iostream>

struct MyType {
    int id;
};

template <typename T>
void show_id(const T& obj) {
    std::cout << obj.id << '\n';
}
    
int main() {
    MyType m{1234};
    show_id(m);
}
