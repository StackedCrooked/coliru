#include <iostream>

const char x[] = "cool string\n"
                 "cool string.";

const char y[] = R"(not so cool string
not so cool string)";

const char z[] = R"(another dumb string
                    another dumb string
                  )";
                  

int main() {
    std::cout << x << '\n' << y << '\n' << z;
}