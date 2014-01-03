#include <iostream>

class Test {

    public:
        Test(std::string, int, float) {
            std::cout << "normal constructor!" << std::endl;
        }

        Test(const char*&, int, float)
        {
            std::cout << "normal constructor 2!" << std::endl;
        }

        template<std::size_t N>
        Test(const char(&)[N], int, float)
        {
            std::cout << "normal constructor 3!" << std::endl;
        }

        template<typename ... Tn>
        Test(Tn ... args) {
            std::cout << "template constructor!" << std::endl;
        }

};

int main() {

    Test t("Hello World!", 42, 0.07f);
    
    const char* c = "Hello World!";
    Test t2(c, 42, 0.07f);

    return 0;

}
