#include <vector>
#include <array>

void SetColor1(const std::vector<float>& color){}
void SetColor2(const std::array<float, 4>& color){}

int main () {
    SetColor1({1, 2, 3, 4});
    SetColor2({1, 2, 3, 4});
}