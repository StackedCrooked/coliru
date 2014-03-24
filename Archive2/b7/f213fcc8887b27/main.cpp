#include <random>
#include <iostream>
 
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int stars = 0;
    unsigned win_count = 0;
    for(unsigned i = 0; i < 10000; ++i) {
        auto result = dis(gen);
        if(result) {
            // won a game
            ++win_count;
            if(win_count > 3) {
                stars += 2;
            }
        }
        else {
            // lost the game
            win_count = 0;
            stars -= 1;
        }
    }
    std::cout << "Total stars: " << stars;
}