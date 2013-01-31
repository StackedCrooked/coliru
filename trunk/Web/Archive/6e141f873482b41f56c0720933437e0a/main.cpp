#include<utility>

int main() {
    int a = 5, b = 7;
    auto pair = std::make_pair<int, int>(a,b);
    return 0;
}