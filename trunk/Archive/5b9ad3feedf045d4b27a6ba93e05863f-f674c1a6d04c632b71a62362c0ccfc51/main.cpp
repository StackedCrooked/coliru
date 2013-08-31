#include <functional>
#include <iostream>


using namespace std::placeholders;

template <typename T>
struct holder{
    ~holder(){
        call_on_delete(hold_this);
    }
    T call_on_delete;
    int hold_this;
};

template <typename T>
holder<T> make_holder(T f, int id){
    return {f, id};
}

void style_a_x(int id) {
    std::cout << "style_a_x(" << id << ")" << std::endl;
}

void style_a_y(int id) {
    std::cout << "style_a_y(" << id << ")" << std::endl;
}

void style_b_x(int i, int* id) {
    std::cout << "style_b_x(" << i << ", " << *id << ")" << std::endl;
}

void style_b_y(int i, int* id) {
    std::cout << "style_b_y(" << i << ", " << *id << ")" << std::endl;
}

int main() {
    auto holder = make_holder([](int a){ style_a_x(a); }, 69);
}