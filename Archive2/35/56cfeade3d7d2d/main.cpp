#include <iostream>

enum class Value {
    Good,
    Bad,
    Ugly
};

int main(int, char*[])
{
    Value v = Value::Ugly;
    switch(v) {
        case Value::Good: std::cout << "Good" << std::endl; break;
        case Value::Bad: std::cout << "Bad" << std::endl; break;
        default:;
    }
    std::cout << "done" << std::endl;
    return 0;
}
