#include <iostream>
#include <tuple>

class enclose {
    class nested {
    public:
        int i = 1337;  
    };
    static nested bla;
public:
    static int get_nested() {return bla.i;}
};

enclose::nested enclose::bla;

int main() {
    std::cout << "nested i: " << enclose::get_nested() << std::endl;
}
