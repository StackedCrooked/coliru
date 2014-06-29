#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

int main() {
    unsigned count = 0;
    for(int x1 = 1; x1 < 10; x1++) {
        for(int x2 = 0; x2 < 10; x2++) {
            for(int x3 = 0; x3 < 10; x3++) {
                for(int x4 = 0; x4 < 10; x4++) {
                    std::unordered_set<int> nums;
                    nums.insert(x1);
                    nums.insert(x2);
                    nums.insert(x3);
                    nums.insert(x4);
                    if (nums.size() <= 3) {
                        ++count;
                        std::cout << x1 << x2 << x3 << x4 << "\n";
                    }
                }
            }
        }
    }
    std::cout << "count: " << count;
}