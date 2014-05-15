#include <array>
#include <string>

struct RecAbbo {
    std::string name;
    std::string surname;
    int games;
    int won;
    int same;
    int lost;
    int place;
    int money;
};
std::array<RecAbbo, 100> Abbo;

void func(RecAbbo&);
void func(RecAbbo const&);

int main() {}