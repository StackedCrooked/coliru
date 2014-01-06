#include <iostream>
class Test {
    public:
        Test(std::pair<char const *, int>) {
            std::cout << "normal constructor 2!" << std::endl;
        }
        template<typename ... Tn>
        explicit Test(Tn...) {
            std::cout << "template constructor!" << std::endl;
        }
};

int main() {
    Test t6({"Test", 42});
    return 0;
}
