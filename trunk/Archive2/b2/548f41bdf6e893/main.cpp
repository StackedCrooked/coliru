#include <iostream>


int main() {
    int max = 200;
    int solution = 0;
    
    for (int p200 = max; p200 >= 0; p200 -= 200) {
        for (int p100 = p200; p100 >= 0; p100 -= 100) {
            for (int p50 = p100; p50 >= 0; p50 -= 50) {
                for (int p20 = p50; p20 >= 0; p20 -= 20) {
                    for (int p10 = p20; p10 >= 0; p10 -= 10) {
                        for (int p5 = p10; p5 >= 0; p5 -= 5) {
                            for (int p2 = p5; p2 >= 0; p2 -= 2) {
                                solution++;
                            }
                        } 
                    }
                } 
            }
        }
    }
    
    std::cout << "Solution: " << solution;
}
    