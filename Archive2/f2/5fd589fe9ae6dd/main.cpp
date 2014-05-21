#include <iostream>
#include <vector>
#include <utility>

class Sesion {
private:
    std::vector<std::pair<int, int>> tablica;
public:
    void save(int x, int y) {
        tablica.emplace_back(x, y);
    }

    void open() {
        for (auto p : tablica)
            std::cout << std::get<0>(p) << ',' << std::get<1>(p) << '\n';
    }
};

int main() {
    Sesion sesion;
    sesion.save(123, 321);
    sesion.save(456, 654);
    sesion.open();
}