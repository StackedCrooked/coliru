#include <iostream>

enum class Flags : int { A = 1, B = 2, C = 4, D = 8 };

template<Flags flag>
struct Foo{    
    void toInt(){
        return static_cast<int>(flag);
    }
};

void countFlags(/* want to take a unkown number of 'foo<>' here, and of any type of foo too */){
    int flags = 0;
    std::cout << "Flags add up to " << flags << "\n";
}

int main(){
    Foo<Flags::A> foo_a;
    Foo<Flags::B> foo_b;
    Foo<Flags::C> foo_c;
    Foo<Flags::D> foo_d;
    countFlags();
    countFlags(foo_a);
    countFlags(foo_a, foo_b);
    countFlags(foo_a, foo_b, foo_c, foo_d);
    return 0;
}