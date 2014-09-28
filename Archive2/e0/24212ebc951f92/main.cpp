#include <random>
#include <iostream>
#include <vector>
#include <string>

int main() {
    const int N = 10;
    std::vector<std::string> square(N, std::string(N, '*'));
    
    for (auto &&row : square) {
        std::cout << row << '\n';
    }
    
    std::mt19937 eng;
    eng.seed(std::random_device{}());

    std::uniform_int_distribution<> dist(0, N-1);
    
    for(int i = 0; i < 6; i++) {
      int x = dist(eng);
      int y = dist(eng);
      
      std::cout << "x:" << x << " y:" << y << "\n\n";
      
      square[y][x] = ' ';
    }
    
    for (auto &&row : square) {
        std::cout << row << '\n';
    }


}
