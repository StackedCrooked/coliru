#include <iostream>
#include <tuple>

class enclose {
    class nested {
        int i = 1337;  
    };
public:
    static int get_nested() {return nested{}.i;}
};

int main() {
    std::cout << "nested i: " << enclose::get_nested() << std::endl;
}
