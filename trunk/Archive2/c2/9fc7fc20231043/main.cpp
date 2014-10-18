#include <vector>
#include <array>
#include <initializer_list>

void SetColor1(const std::vector<float>& color){}
void SetColor2(const std::array<float, 4>& color){}
void SetColor3(const std::initializer_list<float>& color){}

int main () {
    SetColor1({1, 2, 3, 4});
    SetColor2({1, 2, 3, 4});
    SetColor3({1.0f, 2.0f, 3.0f, 4.0f});
}