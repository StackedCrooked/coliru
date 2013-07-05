#include <iostream>
#include <tuple>

enum class Flags : int { A = 1, B = 2, C = 4, D = 8 };

int toInt(Flags flag){
    return static_cast<int>(flag);
}

int main(){
    Flags foo_a = Flags::A;
    Flags foo_b = Flags::B;
    Flags foo_c = Flags::C;
    Flags foo_d = Flags::D;
    int count = 0;
    count += toInt(foo_a);
    std::cout << "Flags add up to " << bar.count << "\n";
    count = 0;
    count += toInt(foo_a) + toInt(foo_b);
    std::cout << "Flags add up to " << bar.count << "\n";
    count = 0;
    count += toInt(foo_a) + toInt(foo_b) + toInt(foo_c) + toInt(foo_d);
    std::cout << "Flags add up to " << bar.count << "\n";
    return 0;
}