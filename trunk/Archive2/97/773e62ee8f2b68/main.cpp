#include <string>
#include <vector>
#include <iostream>

template<typename T, class Tag>
struct SemanticInt{
    explicit SemanticInt(T value) : value(value) {}
    T value;
};

struct Mss : public SemanticInt<int, Mss> {
    Mss(int val) : SemanticInt{val + 2} {}
};

int main()
{
    Mss mss(1);
    std::cout <<  mss.value << std::endl;
}
