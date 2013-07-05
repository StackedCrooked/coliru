#include <iostream>
#include <tuple>

enum class Flags : int { A = 1, B = 2, C = 4, D = 8 };

template<Flags flag>
struct Foo{    
    int toInt(){
        return static_cast<int>(flag);
    }
};

struct Bar{
    int count;
    
    template<typename T>
    void countFlags(T foo){ count += foo.toInt(); }
    
    template<typename First, typename... More>
    void countFlags(First first, More... more){
        countFlags(first);
        countFlags(more...);
    }
    
};

int main(){
    Foo<Flags::A> foo_a;
    Foo<Flags::B> foo_b;
    Foo<Flags::C> foo_c;
    Foo<Flags::D> foo_d;
    Bar bar{0};    
    bar.countFlags(foo_a);
    std::cout << "Flags add up to " << bar.count << "\n";
    bar.count = 0;
    bar.countFlags(foo_a, foo_b);
    std::cout << "Flags add up to " << bar.count << "\n";
    bar.count = 0;
    bar.countFlags(foo_a, foo_b, foo_c, foo_d);
    std::cout << "Flags add up to " << bar.count << "\n";
    return 0;
}