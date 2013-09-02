#include <iostream>
#include <string>
#include <vector>

enum Color {
    RED,
    BLUE,
};

int main() {
    Color color = Color::RED;
    std::cout << color << std::endl;
}