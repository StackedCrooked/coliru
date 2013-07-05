#include <iostream>
#include <tuple>

enum class Type : int { A , B, C, D };

template<Type type>
struct Foo{ int toInt(){ return static_cast<int>(type); } };

struct Bar{
    int count;
    
    template<typename T>
    void countType(T foo){ count += foo.toInt(); }
    
    template<typename First, typename... More>
    void countType(First first, More... more){
        countType(first);
        countType(more...);
    }
    
};

int main(){
    Foo<Type::A> foo_a;
    Foo<Type::B> foo_b;
    Foo<Type::C> foo_c;
    Foo<Type::D> foo_d;
    Bar bar{0};    
    bar.countType(foo_a);
    std::cout << "Type add up to " << bar.count << "\n";
    bar.count = 0;
    bar.countType(foo_a, foo_b);
    std::cout << "Type add up to " << bar.count << "\n";
    bar.count = 0;
    bar.countType(foo_a, foo_b, foo_c, foo_d);
    std::cout << "Type add up to " << bar.count << "\n";
    return 0;
}