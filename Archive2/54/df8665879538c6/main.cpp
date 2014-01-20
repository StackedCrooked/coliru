#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class ext {
public:
    static bool Permutation(const int t1, const int t2) {
        std::vector<int> arr;
        arr.resize(10);

        int temp = t2;
        while (temp > 0) {
            arr[temp % 10]++;
            temp /= 10;
        }

        temp = t1;
        while (temp > 0) {
            arr[temp % 10]--;
            temp /= 10;
        }

        for (int i = 0; i < 10; i++) {
            if (arr[i] != 0) {
                return false;                
            }
        }
        return true;
    }
};

int main() {
    std::vector<int> products = { 2, 3, 4, 5, 6 };
    int solution = 0;
   
    while (true) {
        solution++;
        bool found = false;
        
        if (std::to_string(solution)[0] != '1') {
            continue;    
        }
        
        for (const auto& e : products) {
            if (!ext::Permutation(solution,solution * e)) {
                found = true;
            }
        }
        if (!found) {
            break;    
        }
    }
    
    std::cout << "Solution: " << solution << std::endl;
}