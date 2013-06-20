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

struct uses_holder_for_style_a_x{
    uses_holder_for_style_a_x():
        held_value{&style_a_x, 101}{
    }
        // Here I define what function *this* holder should call on delete
        // But, AFAIK, I can't use the 'make_holder' function
    holder<decltype(&style_a_x)> held_value;
};

int main() {
    auto holdera = make_holder([](int a){ style_a_x(a); }, 69);
    auto holderb = make_holder([](int a){ style_a_y(a); }, 69);
    auto holderc = make_holder([](int& a){ style_b_x(1, &a); }, 69);
    auto holderd = make_holder([](int& a){ style_b_y(1, &a); }, 69);
    
    uses_holder_for_style_a_x the_real_magic;
}