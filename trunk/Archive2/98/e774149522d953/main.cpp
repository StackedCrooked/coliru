#include <iostream>
#include <vector>

class Sesion {
private:
    std::vector<std::vector<int>> tablica;
    
    Sesion() : tablica(2) {}

    void save(int x, int y) {
            tablica[0].push_back(x);
            tablica[1].push_back(y);
    }

    void open() {
        for (int i : tablica[0])
            std::cout << i << '\n';
    }
};

int main() {}